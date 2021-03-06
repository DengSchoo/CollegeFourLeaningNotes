# 【微服务】 微服务入门 2



## 目录

- Nacos配置管理
- Feign远程调用
- Gateway服务网关

## Nacos配置管理

### 目录

- 统一配置管理
- 配置热更新
- 配置共享
- 搭建Nacos集群

### 统一配置管理

> 解决热更新

![image-20211014193443354](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014193443354.png)

在Nacos后台新建配置：

![image-20211014193940403](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014193940403.png)

![image-20211014193957139](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014193957139.png)

> 配置内容不是所有配置 需要更新的配置即可。

### 配置加载过程

![image-20211014194241401](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014194241401.png)

> 先读取nacos文件配置再读取本地配置 最后合并创建spring容器，但是存在一个问题就是nacos的地址配置是在本地的所以需要优先获取。
>
> bootstrap.yml的优先级比application要高所以 需要在bootstrap里面先配置nacos服务地址 

1. 引入Nacos的配置管理客户端依赖

2. 添加bootstrap.yml文件，以下配置决定程序启动nacos取读哪个文件

   1. 当前环境
   2. 服务名称
   3. 文件后缀名

3. 测试

   ```java
       @Value("${pattern.dateformat}")
       private String dateformat;
   
       @GetMapping("now")
       public String now() {
           return LocalDateTime.now().format(DateTimeFormatter.ofPattern(dateformat));
       }
   ```

### 配置自动刷新

> Nacos的配置文件变更后，微服务无需重启就可以感知。不过需要下面两种配置实现，但是需要配置实现：
>
> - 方式一：在@Value注入变量所在类上添加注解@RefreshScope
> - 方式二：使用ConfigurationProperties

#### 方式一：添加注解

```java
@RefreshScope
```

#### 方式二：ConfigurationProperties

```java
@Slf4j
@RestController
@RequestMapping("/user")
//@RefreshScope
public class UserController {

    @Autowired
    private UserService userService;

    /**
     * 路径： /user/110
     *
     * @param id 用户id
     * @return 用户
     */
    @GetMapping("/{id}")
    public User queryById(@PathVariable("id") Long id) {
        return userService.queryById(id, 1);
    }

//    @Value("${pattern.dateformat}")
//    private String dateformat;

    @Autowired
    private PatternProperties patternProperties;

    @GetMapping("now")
    public String now() {
        return LocalDateTime.now().format(DateTimeFormatter.ofPattern(patternProperties.getDateformat()));
    }
}

```

![image-20211014204335165](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014204335165.png)

### 多环境配置共享

![image-20211014204503513](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014204503513.png)

#### 多环境优先级

> 服务名-profile.yaml > 服务名称.yaml > 本地配置

![image-20211014204916603](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014204916603.png)



### Nacos集群

> 生产环境都需要搭建集群 以便高可用

#### Nacos集群搭建

#### 1.集群结构图

官方给出的Nacos集群图：



![image-20210409210621117](https://gitee.com/DengSchoo374/img/raw/master/img/image-20210409210621117.png)

其中包含3个nacos节点，然后一个负载均衡器代理3个Nacos。这里负载均衡器可以使用nginx。

我们计划的集群结构：

![image-20210409211355037](https://gitee.com/DengSchoo374/img/raw/master/img/image-20210409211355037.png)



三个nacos节点的地址：

| 节点   | ip            | port |
| ------ | ------------- | ---- |
| nacos1 | 192.168.150.1 | 8845 |
| nacos2 | 192.168.150.1 | 8846 |
| nacos3 | 192.168.150.1 | 8847 |



#### 2.搭建集群

搭建集群的基本步骤：

- 搭建数据库，初始化数据库表结构
- 下载nacos安装包
- 配置nacos
- 启动nacos集群
- nginx反向代理



##### 2.1.初始化数据库

Nacos默认数据存储在内嵌数据库Derby中，不属于生产可用的数据库。

官方推荐的最佳实践是使用带有主从的高可用数据库集群，主从模式的高可用数据库可以参考**传智教育**的后续高手课程。

这里我们以单点的数据库为例来讲解。

首先新建一个数据库，命名为nacos，而后导入下面的SQL：

```sql
CREATE TABLE `config_info` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT 'id',
  `data_id` varchar(255) NOT NULL COMMENT 'data_id',
  `group_id` varchar(255) DEFAULT NULL,
  `content` longtext NOT NULL COMMENT 'content',
  `md5` varchar(32) DEFAULT NULL COMMENT 'md5',
  `gmt_create` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
  `gmt_modified` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '修改时间',
  `src_user` text COMMENT 'source user',
  `src_ip` varchar(50) DEFAULT NULL COMMENT 'source ip',
  `app_name` varchar(128) DEFAULT NULL,
  `tenant_id` varchar(128) DEFAULT '' COMMENT '租户字段',
  `c_desc` varchar(256) DEFAULT NULL,
  `c_use` varchar(64) DEFAULT NULL,
  `effect` varchar(64) DEFAULT NULL,
  `type` varchar(64) DEFAULT NULL,
  `c_schema` text,
  PRIMARY KEY (`id`),
  UNIQUE KEY `uk_configinfo_datagrouptenant` (`data_id`,`group_id`,`tenant_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='config_info';

/******************************************/
/*   数据库全名 = nacos_config   */
/*   表名称 = config_info_aggr   */
/******************************************/
CREATE TABLE `config_info_aggr` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT 'id',
  `data_id` varchar(255) NOT NULL COMMENT 'data_id',
  `group_id` varchar(255) NOT NULL COMMENT 'group_id',
  `datum_id` varchar(255) NOT NULL COMMENT 'datum_id',
  `content` longtext NOT NULL COMMENT '内容',
  `gmt_modified` datetime NOT NULL COMMENT '修改时间',
  `app_name` varchar(128) DEFAULT NULL,
  `tenant_id` varchar(128) DEFAULT '' COMMENT '租户字段',
  PRIMARY KEY (`id`),
  UNIQUE KEY `uk_configinfoaggr_datagrouptenantdatum` (`data_id`,`group_id`,`tenant_id`,`datum_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='增加租户字段';


/******************************************/
/*   数据库全名 = nacos_config   */
/*   表名称 = config_info_beta   */
/******************************************/
CREATE TABLE `config_info_beta` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT 'id',
  `data_id` varchar(255) NOT NULL COMMENT 'data_id',
  `group_id` varchar(128) NOT NULL COMMENT 'group_id',
  `app_name` varchar(128) DEFAULT NULL COMMENT 'app_name',
  `content` longtext NOT NULL COMMENT 'content',
  `beta_ips` varchar(1024) DEFAULT NULL COMMENT 'betaIps',
  `md5` varchar(32) DEFAULT NULL COMMENT 'md5',
  `gmt_create` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
  `gmt_modified` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '修改时间',
  `src_user` text COMMENT 'source user',
  `src_ip` varchar(50) DEFAULT NULL COMMENT 'source ip',
  `tenant_id` varchar(128) DEFAULT '' COMMENT '租户字段',
  PRIMARY KEY (`id`),
  UNIQUE KEY `uk_configinfobeta_datagrouptenant` (`data_id`,`group_id`,`tenant_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='config_info_beta';

/******************************************/
/*   数据库全名 = nacos_config   */
/*   表名称 = config_info_tag   */
/******************************************/
CREATE TABLE `config_info_tag` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT 'id',
  `data_id` varchar(255) NOT NULL COMMENT 'data_id',
  `group_id` varchar(128) NOT NULL COMMENT 'group_id',
  `tenant_id` varchar(128) DEFAULT '' COMMENT 'tenant_id',
  `tag_id` varchar(128) NOT NULL COMMENT 'tag_id',
  `app_name` varchar(128) DEFAULT NULL COMMENT 'app_name',
  `content` longtext NOT NULL COMMENT 'content',
  `md5` varchar(32) DEFAULT NULL COMMENT 'md5',
  `gmt_create` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
  `gmt_modified` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '修改时间',
  `src_user` text COMMENT 'source user',
  `src_ip` varchar(50) DEFAULT NULL COMMENT 'source ip',
  PRIMARY KEY (`id`),
  UNIQUE KEY `uk_configinfotag_datagrouptenanttag` (`data_id`,`group_id`,`tenant_id`,`tag_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='config_info_tag';

/******************************************/
/*   数据库全名 = nacos_config   */
/*   表名称 = config_tags_relation   */
/******************************************/
CREATE TABLE `config_tags_relation` (
  `id` bigint(20) NOT NULL COMMENT 'id',
  `tag_name` varchar(128) NOT NULL COMMENT 'tag_name',
  `tag_type` varchar(64) DEFAULT NULL COMMENT 'tag_type',
  `data_id` varchar(255) NOT NULL COMMENT 'data_id',
  `group_id` varchar(128) NOT NULL COMMENT 'group_id',
  `tenant_id` varchar(128) DEFAULT '' COMMENT 'tenant_id',
  `nid` bigint(20) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`nid`),
  UNIQUE KEY `uk_configtagrelation_configidtag` (`id`,`tag_name`,`tag_type`),
  KEY `idx_tenant_id` (`tenant_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='config_tag_relation';

/******************************************/
/*   数据库全名 = nacos_config   */
/*   表名称 = group_capacity   */
/******************************************/
CREATE TABLE `group_capacity` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `group_id` varchar(128) NOT NULL DEFAULT '' COMMENT 'Group ID，空字符表示整个集群',
  `quota` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '配额，0表示使用默认值',
  `usage` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '使用量',
  `max_size` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '单个配置大小上限，单位为字节，0表示使用默认值',
  `max_aggr_count` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '聚合子配置最大个数，，0表示使用默认值',
  `max_aggr_size` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '单个聚合数据的子配置大小上限，单位为字节，0表示使用默认值',
  `max_history_count` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '最大变更历史数量',
  `gmt_create` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
  `gmt_modified` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '修改时间',
  PRIMARY KEY (`id`),
  UNIQUE KEY `uk_group_id` (`group_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='集群、各Group容量信息表';

/******************************************/
/*   数据库全名 = nacos_config   */
/*   表名称 = his_config_info   */
/******************************************/
CREATE TABLE `his_config_info` (
  `id` bigint(64) unsigned NOT NULL,
  `nid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `data_id` varchar(255) NOT NULL,
  `group_id` varchar(128) NOT NULL,
  `app_name` varchar(128) DEFAULT NULL COMMENT 'app_name',
  `content` longtext NOT NULL,
  `md5` varchar(32) DEFAULT NULL,
  `gmt_create` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `gmt_modified` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `src_user` text,
  `src_ip` varchar(50) DEFAULT NULL,
  `op_type` char(10) DEFAULT NULL,
  `tenant_id` varchar(128) DEFAULT '' COMMENT '租户字段',
  PRIMARY KEY (`nid`),
  KEY `idx_gmt_create` (`gmt_create`),
  KEY `idx_gmt_modified` (`gmt_modified`),
  KEY `idx_did` (`data_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='多租户改造';


/******************************************/
/*   数据库全名 = nacos_config   */
/*   表名称 = tenant_capacity   */
/******************************************/
CREATE TABLE `tenant_capacity` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT '主键ID',
  `tenant_id` varchar(128) NOT NULL DEFAULT '' COMMENT 'Tenant ID',
  `quota` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '配额，0表示使用默认值',
  `usage` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '使用量',
  `max_size` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '单个配置大小上限，单位为字节，0表示使用默认值',
  `max_aggr_count` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '聚合子配置最大个数',
  `max_aggr_size` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '单个聚合数据的子配置大小上限，单位为字节，0表示使用默认值',
  `max_history_count` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '最大变更历史数量',
  `gmt_create` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
  `gmt_modified` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '修改时间',
  PRIMARY KEY (`id`),
  UNIQUE KEY `uk_tenant_id` (`tenant_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='租户容量信息表';


CREATE TABLE `tenant_info` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT 'id',
  `kp` varchar(128) NOT NULL COMMENT 'kp',
  `tenant_id` varchar(128) default '' COMMENT 'tenant_id',
  `tenant_name` varchar(128) default '' COMMENT 'tenant_name',
  `tenant_desc` varchar(256) DEFAULT NULL COMMENT 'tenant_desc',
  `create_source` varchar(32) DEFAULT NULL COMMENT 'create_source',
  `gmt_create` bigint(20) NOT NULL COMMENT '创建时间',
  `gmt_modified` bigint(20) NOT NULL COMMENT '修改时间',
  PRIMARY KEY (`id`),
  UNIQUE KEY `uk_tenant_info_kptenantid` (`kp`,`tenant_id`),
  KEY `idx_tenant_id` (`tenant_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='tenant_info';

CREATE TABLE `users` (
	`username` varchar(50) NOT NULL PRIMARY KEY,
	`password` varchar(500) NOT NULL,
	`enabled` boolean NOT NULL
);

CREATE TABLE `roles` (
	`username` varchar(50) NOT NULL,
	`role` varchar(50) NOT NULL,
	UNIQUE INDEX `idx_user_role` (`username` ASC, `role` ASC) USING BTREE
);

CREATE TABLE `permissions` (
    `role` varchar(50) NOT NULL,
    `resource` varchar(255) NOT NULL,
    `action` varchar(8) NOT NULL,
    UNIQUE INDEX `uk_role_permission` (`role`,`resource`,`action`) USING BTREE
);

INSERT INTO users (username, password, enabled) VALUES ('nacos', '$2a$10$EuWPZHzz32dJN7jexM34MOeYirDdFAZm2kuWj7VEOJhhZkDrxfvUu', TRUE);

INSERT INTO roles (username, role) VALUES ('nacos', 'ROLE_ADMIN');
```



##### 2.2.下载nacos

nacos在GitHub上有下载地址：https://github.com/alibaba/nacos/tags，可以选择任意版本下载。

本例中才用1.4.1版本：

![image-20210409212119411](https://gitee.com/DengSchoo374/img/raw/master/img/image-20210409212119411.png)









##### 2.3.配置Nacos

将这个包解压到任意非中文目录下，如图：

![image-20210402161843337](https://gitee.com/DengSchoo374/img/raw/master/img/image-20210402161843337.png)

目录说明：

- bin：启动脚本
- conf：配置文件



进入nacos的conf目录，修改配置文件cluster.conf.example，重命名为cluster.conf：

![image-20210409212459292](https://gitee.com/DengSchoo374/img/raw/master/img/image-20210409212459292.png)

然后添加内容：

```
127.0.0.1:8845
127.0.0.1.8846
127.0.0.1.8847
```



然后修改application.properties文件，添加数据库配置

```properties
spring.datasource.platform=mysql

db.num=1

db.url.0=jdbc:mysql://127.0.0.1:3306/nacos?characterEncoding=utf8&connectTimeout=1000&socketTimeout=3000&autoReconnect=true&useUnicode=true&useSSL=false&serverTimezone=UTC
db.user.0=root
db.password.0=123
```



##### 2.4.启动

将nacos文件夹复制三份，分别命名为：nacos1、nacos2、nacos3

![image-20210409213335538](https://gitee.com/DengSchoo374/img/raw/master/img/image-20210409213335538.png) 

然后分别修改三个文件夹中的application.properties，

nacos1:

```properties
server.port=8845
```

nacos2:

```properties
server.port=8846
```

nacos3:

```properties
server.port=8847
```



然后分别启动三个nacos节点：

```
startup.cmd
```



##### 2.5.nginx反向代理

找到课前资料提供的nginx安装包： 

![image-20210410103253355](https://gitee.com/DengSchoo374/img/raw/master/img/image-20210410103253355.png) 

解压到任意非中文目录下：

![image-20210410103322874](https://gitee.com/DengSchoo374/img/raw/master/img/image-20210410103322874.png) 

修改conf/nginx.conf文件，配置如下：

```nginx
upstream nacos-cluster {
    server 127.0.0.1:8845;
	server 127.0.0.1:8846;
	server 127.0.0.1:8847;
}

server {
    listen       80;
    server_name  localhost;

    location /nacos {
        proxy_pass http://nacos-cluster;
    }
}
```



而后在浏览器访问：http://localhost/nacos即可。



代码中application.yml文件配置如下：

```yaml
spring:
  cloud:
    nacos:
      server-addr: localhost:80 # Nacos地址
```







##### 2.6.优化



- 实际部署时，需要给做反向代理的nginx服务器设置一个域名，这样后续如果有服务器迁移nacos的客户端也无需更改配置.

- Nacos的各个节点应该部署到多个不同服务器，做好容灾和隔离

![image-20211014210120338](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014210120338.png)



## Feign远程调用

![image-20211014210518565](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014210518565.png)

### RestTemplate方式调用存在的问题

```java
//String url = "http://localhost:8081/user/" + order.getUserId();
        String url = "http://user-service/user/" + order.getUserId();
        // 2.2 发起http请求 实现远程调用
        User user = restTemplate.getForObject(url, User.class);
        // 3 封装user到Order
        order.setUser(user);
```

- 代码可读性差，编程体验不统一
- 参数复杂URL难以维护

### Http客户端Feign

> 声明式Http客户端，优雅实现http请求的发送，解决上面提到的问题。
>
> 声明式：只有提供对应的信息 自动发送http请求

#### 定义和使用Feign客户端

1. 引入依赖

   ```xml
   <!--Feign依赖-->
           <dependency>
               <groupId>org.springframework.cloud</groupId>
               <artifactId>spring-cloud-starter-openfeign</artifactId>
           </dependency>
   ```

   

2. 在order-service的启动类加注解开启feign功能

   ```java
   @EnableFeignClients
   public class OrderApplication {
   
       public static void main(String[] args) {
           SpringApplication.run(OrderApplication.class, args);
       }
   
       /*
           创建RestTemplateBean
        */
       @Bean
       @LoadBalanced
       public RestTemplate restTemplate() {
           return new RestTemplate();
       }
   
       // 将全局负载均衡规则改为randomRule
   //    @Bean
   //    public IRule randomRule() { return new RandomRule(); }
   
   }
   ```

   

3. 编写Feign客户端(声明远程调用)

   ```java
   @FeignClient("user-service")
   public interface UserClient {
       @GetMapping("/user/{id}")
       User findById(@PathVariable("id")Long id);
   }
   ```

   



![image-20211014211637543](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014211637543.png)

### 自定义配置

![image-20211014212003122](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014212003122.png)

- Logger.Level: None没有日志，BASIC开始结束时间，HEADERS：带上头部，FULL全部

#### 配置方法一：配置文件

- 全局配置

  ```yaml
  feign:
    client:
      config:
        default: # 用default就是全局配置 如果写特定服务名称就是针对某个微服务的配置
  ```

- 局部配置

  ```yaml
  feign:
    client:
      config:
        user-service:
          loggerLevel: FULL
  ```

#### 配置方法二：java代码方法

首先需要声明一个Bean

```java
public class FeignClientConfiguration {
    @Bean
    public Logger.Level feignLogLevel(){
        return Logger.Level.BASIC; 
    }
}
```

- 如果是全局配置，把它放到`@EnableFeignClients`这个注解中

  `@EnableFeignClients(defaultConfiguration = FeignClientConfiguration.class) `

- 如果是局部配置，把它放到`@FeignClient`这个注解中

  `@FeignClient(value = "userservice", configuration = FeignClientConfiguration.class) `

![image-20211014213451897](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014213451897.png)

### 性能优化

![image-20211014213710500](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014213710500.png)



#### feign性能优化 - 连接池配置

添加HttpClient的支持

1. 引入依赖：

```xml
io.github.opengeign
feign-httpclient
```

2. 配置连接池

```yaml
feign:
	client:
		config:
			default: # default全局的配置
				loggerLevel: BASIC # 日志级别，BASIC就是基本的请求和响应信息 
     httpclient:
     	enabled: true # 开启feign对HttpClient的支持
        max-connections: 200 # 最大的连接数 根据业务进行测试 经验值
        max-connections-per-route: 50 # 每个路径的最大连接数

```



![image-20211014221026731](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014221026731.png)

### feign的最佳实践

#### 实践一：controller和FeignClient继承同一个接口

![image-20211014221433781](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014221433781.png)

#### 实践二：将FeignClient、POJO、Feign的默认配置都定义到一个模块中，供所有消费者使用。

![image-20211014221634217](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014221634217.png)

#### 实践二的步骤

![image-20211014221850842](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014221850842.png)

![image-20211014223234522](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014223234522.png)

## Gateway服务网关



### 目录

- 为什么需要网关
- gateway快速入门
- 断言工厂
- 过滤器工厂
- 全局过滤器
- 跨域问题

### 为什么需要网关

- 身份认证和权限校验、
- 服务路由、负载均衡
- 请求限流

![image-20211015214316302](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211015214316302.png)

### 网关技术实现

> SpringCloud在网关的实现有两种：
>
> - gateway
> - zuul
>
> Zuul是基于Servelet的实现，属于阻塞式编程。而SpringCloudGateway则是基于Spring5中提供的WebFlux，属于响应式编程的实现，具备更好的性能。

### 搭建网关服务

步骤：

1. 创建新的module，引入SpringCloudGateway的依赖和nacos服务发现依赖

   ```xml
           <dependency>
               <groupId>com.alibaba.cloud</groupId>
               <artifactId>spring-cloud-starter-alibaba-nacos-discovery</artifactId>
           </dependency>
   
           <dependency>
               <groupId>org.springframework.cloud</groupId>
               <artifactId>spring-cloud-starter-gateway</artifactId>
           </dependency>
   ```

   

2. 编写路由配置及nacos地址

   ```yaml
   server:
     port: 10010 # 网关端口
   spring:
     application:
       name: gateway
     cloud:
       nacos:
         server-addr: localhost:8848 # nacos地址
       gateway:
         routes: # 网关路由配置
           - id: user-service
             uri: lb://user-service # 路由的目标地址 lb就是负载均衡 后面跟服务名
             predicates: # 路由断言 判断请求是否符合路由规则的条件
               - Path=/user/** # 按照路径匹配
             filter:
               - AddRequestHeader=Truth, Deng
           - id: order-service
             uri: lb://orderservice
             predicates:
               - Path=/user/**
   ```

![image-20211015220048776](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211015220048776.png)

### 路由断言工厂Route Predicate Factory

网关路由可以配置的内容包括：

- 路由id：路由唯一标示
- uri：路由目的地，支持lb和http两种
- predicates：路由断言，判断请求是否符合要求，符合转发道路由目的地
- filters：路由过滤器

> 断言工厂：将配置文件中的字符串解析，转变为路由条件。断言工厂在SpringCloudGateway中还有十几个。

![image-20211015220616504](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211015220616504.png)

### 路由过滤器 GatewayFilter

> 过滤器，可以对进入网关和微服务返回的响应做处理。

![image-20211015221107567](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211015221107567.png)

#### 过滤器工厂Filter Factories

> 见名知意

![image-20211015221248453](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211015221248453.png)

#### 案例

> 给所有userservice添加一个请求头
>
> ```yaml
> filter:
>   - AddRequestHeader=Truth, Deng
> ```

如果需要对所有路由都生效 则可以将过滤器写道default下：

```yaml
server:
  port: 10010 # 网关端口
spring:
  application:
    name: gateway
  cloud:
    nacos:
      server-addr: localhost:8848 # nacos地址
    gateway:
      routes: # 网关路由配置
        - id: user-service
          uri: lb://user-service # 路由的目标地址 lb就是负载均衡 后面跟服务名
          predicates: # 路由断言 判断请求是否符合路由规则的条件
            - Path=/user/** # 按照路径匹配
          filter:
            - AddRequestHeader=Truth, Deng
        - id: order-service
          uri: lb://orderservice
          predicates:
            - Path=/user/**
      default-filters:
        - AddRequestHeader=Truth, Deng
```

### 路由过滤器GlobalFilter

> 作用于一切进入网关的请求和微服务响应，与GatewayFilter作用一样。
>
> 区别：处理逻辑自定义。GlobalFilter的逻辑需要自己来写。
>
> 定义方式是实现GlobalFilter接口。

![image-20211015222249803](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211015222249803.png)

#### 案例：定义全局过滤器，拦截并判断用户身份

需求：定义全局过滤器， 拦截请求，判断请求的参数是否满足下面条件

- 参数中是否有authorization
- authorization参数值是否是admin

同时满足则放行。

```java
@Component  // 注入道Spring 容器中
@Order(-1) // 表示Filter的优先级 也可以实现接口Ordered 实现方法
public class AuthorizeFilter implements GlobalFilter {

    // 基于响应式编程的API
    @Override
    public Mono<Void> filter(ServerWebExchange exchange, GatewayFilterChain chain) {
        // 1. 获取请求参数
        ServerHttpRequest request = exchange.getRequest();
        MultiValueMap<String, String> queryParams = request.getQueryParams();
        // 2. 获取参数中的 authorization 参数
        String auth = queryParams.getFirst("authorization");
        // 3. 判断参数值是否等于admin
        if ("admin".equals(auth)) {
            // 4. 是 放行
            return chain.filter(exchange);
        }
        // 设置状态码
        exchange.getResponse().setStatusCode(HttpStatus.UNAUTHORIZED);

        // 5. 否 拦截
        return exchange.getResponse().setComplete();
    }
}

```

### 过滤器执行顺序

- 当前路由
- Default路由
- Global路由

在请求路由后，会将当前路由过滤器、默认路由过滤器、Global过滤器合并到一个过滤器链中，排序后一次执行每个过滤器。

![image-20211015223602432](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211015223602432.png)

> Global Filter被适配为Gateway Filter

![image-20211015224039786](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211015224039786.png)

![image-20211015224120615](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211015224120615.png)

### 跨域问题处理

#### 跨域问题

- 域名不同
- 域名相同，端口不同

> 跨域问题：浏览器禁止请求的发起者与服务端发生跨域ajax请求，请求被浏览器拦截的问题。
>
> 解决方案：CORS

#### CORS配置

> 浏览器询问服务端能否运行跨域。

![image-20211015224518531](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211015224518531.png)

![image-20211015224622399](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211015224622399.png)

![image-20211015224709875](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211015224709875.png)

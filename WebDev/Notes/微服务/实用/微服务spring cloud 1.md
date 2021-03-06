# 【微服务】微服务入门 1

## 目录

- 认识微服务
- 分布式服务架构案例
- eureka注册中心
- Ribbon负载均衡原理
- nacos注册中心

## 认识微服务

### 单体架构

> 业务的所有功能集中在一个项目中开发，打成一个包部署

#### 优点

- 架构简单
- 部署成本低

#### 缺点

- 耦合度高

### 分布式架构

> 根据业务功能对系统进行拆分，每个业务模块作为独立项目开发，称为一个服务。

![image-20211011161449052](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211011161449052.png)

#### 优点

- 降低服务耦合
- 有利于服务升级拓展

#### 分布式需要考虑的问题

- 服务拆分粒度如何？
- 服务集群地址如何维护？
- 服务之间如何实现远程调用？
- 服务健康状态如何感知？

### 微服务

> 微服务是一种经过良好架构设计的分布式架构方案，微服务架构特征。

#### 设计原则：实现是高内聚低耦合

- 单一职责：微服务拆分粒度更小，每一个服务都对应唯一的业务能力，避免重复业务开发

- 面向服务：微服务对外暴漏业务接口

- 自治：团队独立、技术独立、数据独立、部署独立

- 隔离性强：服务做好隔离、容错、降级、避免出现级联现象

  

![image-20211011162143169](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211011162143169.png)

### 微服务结构

![image-20211011162329113](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211011162329113.png)

### 微服务技术对比

![image-20211011162856144](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211011162856144.png)

### 企业需求

![image-20211011162911527](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211011162911527.png)

## SpringCloud

> 目前国内使用最广泛的微服务框架。
>
> https://cloud.spring.io/

![image-20211011163233326](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211011163233326.png)

### 与SpringBoot版本兼容关系

![image-20211011163445868](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211011163445868.png)

> 使用Hoxton.SR10，对应SB2.3.x

## 服务拆分及远程调用

### 服务拆分注意事项

1. 不同微服务，不要重复开发相同业务
2. 微服务数据独立，不要访问其它微服务的数据库
3. 将自己的部分业务暴漏接口，供其它微服务调用





## Eureka注册中心

> 面临的问题：
>
> - 服务消费者如何获得服务提供者的地址信息
> - 如果多个服务提供者 应该如何选择
> - 消费者如何得知提供者的服务健康状态

### 作用

 ![image-20211011180727159](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211011180727159.png)

### 解决问题

> 面临的问题：
>
> - 服务消费者如何获得服务提供者的地址信息
>   - 服务提供者启动时会向eureka注册自己的信息
>   - eureka保存这些信息
>   - 消费者根据服务名称向eureka拉去提供者信息
> - 如果多个服务提供者 应该如何选择
>   - Load Balance 从服务列表中挑选一个
> - 消费者如何得知提供者的服务健康状态
>   - 服务提供者妹30s向Eureka Server发送心跳请求，报告健康状态
>   - eureka会更新服务列表信息，心跳不正常被剔除
>   - 消费者就可以拉去到最新的信息

### 动手实践

![image-20211011202644465](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211011202644465.png)

#### 搭建注册中心

> 搭建Eureka Server

搭建步骤：

1. 创建项目 引入server依赖

   ```xml
   <!--eureka注册中心-->
           <dependency>
               <groupId>org.springframework.cloud</groupId>
               <artifactId>spring-cloud-starter-netflix-eureka-server</artifactId>
           </dependency>
   ```

   

2. 编写启动类

   ```java
   package com.deng.eureka;
   
   import org.springframework.boot.SpringApplication;
   import org.springframework.boot.autoconfigure.SpringBootApplication;
   import org.springframework.cloud.netflix.eureka.server.EnableEurekaServer;
   
   //开启Eureka注解
   @EnableEurekaServer
   @SpringBootApplication
   public class EurekaApplication {
       public static void main(String[] args) {
           SpringApplication.run(EurekaApplication.class, args);
       }
   }
   
   ```

   

3. 添加application.yml文件 编写配置

   ```yaml
   server:
     port: 10086
   spring:
     application:
       name: eureka-server
   eureka:
     client:
       service-url:
         defaultZone: http://127.0.0.1:10086/eureka
   

#### 服务注册

> 将user-service、Order-service都注册到eureka

1. 引入Client依赖

   ```xml
   <!--eureka注册中心-->
           <dependency>
               <groupId>org.springframework.cloud</groupId>
               <artifactId>spring-cloud-starter-netflix-eureka-client</artifactId>
           </dependency>
   ```

   

2. 配置eureka-server地址

   ```yaml
   server:
     port: 8081
   spring:
     application:
       name: user-service
   eureka:
     client:
       service-url:
         defaultZone: http://127.0.0.1:10086/eureka
   ```

   > 可以通过![image-20211011211817641](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211011211817641.png)
   >
   > ![image-20211011211856120](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211011211856120.png)
   >
   > 开启多个服务

#### 服务发现

> 无论消费者还是提供者只要引入了依赖就都会注册到注册中心去。
>
> 负载均衡挑选一个服务 实现远程调用



## Ribbon负载均衡

### 负载均衡原理

![image-20211013202341556](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211013202341556.png)

- IRule负载均衡接口

### 负载均衡规则

![image-20211013202429044](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211013202429044.png)

![image-20211013202523641](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211013202523641.png)



### 负载均衡配置

#### 全局配置

```java
// 全局负载均衡配置: 在application中 或者在配置类中配置
    @Bean
    public IRule randomRule() { return new RandomRule(); }
```

#### 局部配置

```yaml
# 在对应yml文件中配置
user-service:
  ribbon:
    NFLoadBalancerRuleClassName: com.netflix.loadbalancer.RandomRule
```

### 饥饿加载

> Ribbon默认懒加载：在第一次访问的时候采取创建loadBalanceClient，请求时间会变长，而饥饿加载则会项目启动时

```yaml
ribbon:
  eager-load:
    enabled: true # 开启饥饿加载
    clients: # 指定饥饿加载的服务名称 - 列表
      - user-service
```

![image-20211013205015326](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211013205015326.png)

## Nacos注册中心

> 相比Eureka功能更加丰富

### Nacos安装

#### 1.Windows安装

开发阶段采用单机安装即可。

##### 1.1.下载安装包

在Nacos的GitHub页面，提供有下载链接，可以下载编译好的Nacos服务端或者源代码：

GitHub主页：https://github.com/alibaba/nacos

GitHub的Release下载页：https://github.com/alibaba/nacos/releases

如图：

![image-20210402161102887](https://gitee.com/DengSchoo374/img/raw/master/img/image-20210402161102887.png)



本课程采用1.4.1.版本的Nacos，课前资料已经准备了安装包：

![image-20210402161130261](D:\Study\课程\3、史上最全面的微服务技术课程\实用篇\学习资料\day01-SpringCloud01\资料\assets\image-20210402161130261.png)

windows版本使用`nacos-server-1.4.1.zip`包即可。



##### 1.2.解压

将这个包解压到任意非中文目录下，如图：

![image-20210402161843337](D:\Study\课程\3、史上最全面的微服务技术课程\实用篇\学习资料\day01-SpringCloud01\资料\assets\image-20210402161843337.png)

目录说明：

- bin：启动脚本
- conf：配置文件



##### 1.3.端口配置

Nacos的默认端口是8848，如果你电脑上的其它进程占用了8848端口，请先尝试关闭该进程。

**如果无法关闭占用8848端口的进程**，也可以进入nacos的conf目录，修改配置文件中的端口：

![image-20210402162008280](D:\Study\课程\3、史上最全面的微服务技术课程\实用篇\学习资料\day01-SpringCloud01\资料\assets\image-20210402162008280.png)

修改其中的内容：

![image-20210402162251093](D:\Study\课程\3、史上最全面的微服务技术课程\实用篇\学习资料\day01-SpringCloud01\资料\assets\image-20210402162251093.png)



##### 1.4.启动

启动非常简单，进入bin目录，结构如下：

![image-20210402162350977](D:\Study\课程\3、史上最全面的微服务技术课程\实用篇\学习资料\day01-SpringCloud01\资料\assets\image-20210402162350977.png)

然后执行命令即可：

- windows命令：

  ```
  startup.cmd -m standalone # 单例模式启动
  ```


执行后的效果如图：

![image-20210402162526774](D:\Study\课程\3、史上最全面的微服务技术课程\实用篇\学习资料\day01-SpringCloud01\资料\assets\image-20210402162526774.png)



##### 1.5.访问

在浏览器输入地址：http://127.0.0.1:8848/nacos即可：

![image-20210402162630427](D:\Study\课程\3、史上最全面的微服务技术课程\实用篇\学习资料\day01-SpringCloud01\资料\assets\image-20210402162630427.png)

默认的账号和密码都是nacos，进入后：

![image-20210402162709515](D:\Study\课程\3、史上最全面的微服务技术课程\实用篇\学习资料\day01-SpringCloud01\资料\assets\image-20210402162709515.png)





#### 2.Linux安装

Linux或者Mac安装方式与Windows类似。

##### 2.1.安装JDK

Nacos依赖于JDK运行，索引Linux上也需要安装JDK才行。

上传jdk安装包：

![image-20210402172334810](D:\Study\课程\3、史上最全面的微服务技术课程\实用篇\学习资料\day01-SpringCloud01\资料\assets\image-20210402172334810.png)

上传到某个目录，例如：`/usr/local/`



然后解压缩：

```sh
tar -xvf jdk-8u144-linux-x64.tar.gz
```

然后重命名为java



配置环境变量：

```sh
export JAVA_HOME=/usr/local/java
export PATH=$PATH:$JAVA_HOME/bin
```

设置环境变量：

```sh
source /etc/profile
```





##### 2.2.上传安装包

如图：

![image-20210402161102887](https://gitee.com/DengSchoo374/img/raw/master/img/image-20210402161102887.png)

也可以直接使用课前资料中的tar.gz：

![image-20210402161130261](D:\Study\课程\3、史上最全面的微服务技术课程\实用篇\学习资料\day01-SpringCloud01\资料\assets\image-20210402161130261.png)

上传到Linux服务器的某个目录，例如`/usr/local/src`目录下：

![image-20210402163715580](https://gitee.com/DengSchoo374/img/raw/master/img/image-20210402163715580.png)



##### 2.3.解压

命令解压缩安装包：

```sh
tar -xvf nacos-server-1.4.1.tar.gz
```

然后删除安装包：

```sh
rm -rf nacos-server-1.4.1.tar.gz
```

目录中最终样式：

![image-20210402163858429](D:\Study\课程\3、史上最全面的微服务技术课程\实用篇\学习资料\day01-SpringCloud01\资料\assets\image-20210402163858429.png)

目录内部：

![image-20210402164414827](https://gitee.com/DengSchoo374/img/raw/master/img/image-20210402164414827.png)



##### 2.4.端口配置

与windows中类似



##### 2.5.启动

在nacos/bin目录中，输入命令启动Nacos：

```sh
sh startup.sh -m standalone
```







#### 3.Nacos的依赖

父工程：

```xml
<dependency>
    <groupId>com.alibaba.cloud</groupId>
    <artifactId>spring-cloud-alibaba-dependencies</artifactId>
    <version>2.2.5.RELEASE</version>
    <type>pom</type>
    <scope>import</scope>
</dependency>
```



客户端：

```xml
<!-- nacos客户端依赖包 -->
<dependency>
    <groupId>com.alibaba.cloud</groupId>
    <artifactId>spring-cloud-starter-alibaba-nacos-discovery</artifactId>
</dependency>

```

### 服务注册

1. 父工程引入spring-cloud-alibaba管理依赖

   ```xml
   <dependency>
       <groupId>com.alibaba.cloud</groupId>
       <artifactId>spring-cloud-alibaba-dependencies</artifactId>
       <version>2.2.6.RELEASE</version>
       <type>pom</type>
       <scope>import</scope>
   </dependency>
   ```

   

2. 添加客户端依赖

   ```xml
   <!-- nacos客户端依赖 -->
   <dependency>
       <groupId>com.alibaba.cloud</groupId>
       <artifactId>spring-cloud-starter-alibaba-nacos-discovery</artifactId>
   </dependency>
   
   ```

3. 修改yml nacos配置

   ```yaml
   spring:
     application:
       name: order-service
     cloud: 
       nacos:
         server-addr: localhost:8848
   ```

   ![image-20211014111835731](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014111835731.png)

### 服务分级存储模型

> 新加第二层集群概念，按照地域增加集群的概念

![image-20211014112032800](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014112032800.png)

#### 好处

>  选择本地服务更加快速、相应更快,解决服务跨集群调用问题, 本地集群不可用再取其它集群访问。

#### 集群属性配置

```yaml
spring:
  application:
    name: order-service
  cloud: 
    nacos:
      server-addr: localhost:8848
      discovery:
        cluster-name: HZ # 配置集群
```

### NacosRule负载均衡

在order-service中：

```yaml
user-service:
  ribbon:
  	NFLoadBalancerRuleClassName: com.alibaba.cloud.nacos.ribbon.NacosRule
    # NFLoadBalancerRuleClassName: com.netflix.loadbalancer.RandomRule
```

> 优先访问本地 如果本地集群不可用 则会跨集群调用

### 带权负载均衡

> 根据机器性能 分配不同权重 在后台控制台 修改权重即可(0 ~ 1)
>
> 根据负载均衡就可以进行灰度发布 平滑过渡版本

### 环境隔离 - namespace

> 不同环境下的服务不可见

![image-20211014113358470](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014113358470.png)

![image-20211014113500507](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014113500507.png)

![image-20211014113521783](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014113521783.png)

![image-20211014113532289](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014113532289.png)

![image-20211014113548209](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014113548209.png)

```yaml
spring:
  application:
    name: order-service
  cloud: 
    nacos:
      server-addr: localhost:8848
      discovery:
        cluster-name: HZ # 配置集群
        namespace: xxxxx(Id) # 命名空间ID
```

### Nacos与eureka的区别

#### nacos注册中心细节

![image-20211014114236433](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014114236433.png)

- 为了提高效率 在客户端增加 缓存机制 缓存服务信息 减少与注册中心请求的次数
- 区分不同实例
  - 临时实例：采用心跳包的机制
  - 非临时实例：nacos主动访问
- 对于服务提供者的信息进行主动推送变更消息 提供容错性

![image-20211014114531368](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211014114531368.png)

```yaml
spring:
  application:
    name: order-service
  cloud: 
    nacos:
      server-addr: localhost:8848
      discovery:
        cluster-name: HZ # 配置集群
        namespace: xxxxx(Id) # 命名空间ID
        ephermeral: false # 是否是临时实例
```


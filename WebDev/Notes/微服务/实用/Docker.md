# Docker

## 初识Docker

### 什么是Docker

项目部署的问题：大型项目组件多，运行环境也比较复杂，部署时会碰到一些问题

- 依赖关系复杂，容易出现兼容性问题
- 开发、测试、生产环境有差异

Docker 解决思路：

![image-20211016220016964](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016220016964.png)



![image-20211016220154571](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016220154571.png)

![image-20211016220220083](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016220220083.png)





### Docker和虚拟机的区别

![image-20211016220315189](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016220315189.png)



![image-20211016220340854](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016220340854.png)

差异：

- Docker是一个系统进程；虚拟机是在操作系统中的操作系统
- docker体积小、启动速度块、性能好；虚拟机体积大、启动速度慢、性能一般。



### Docker架构

#### 镜像和容器

- 镜像(image): Docker将应用程序及其需要的依赖、函数库、环境、配置等文件打包在一起，成为镜像。
- 容器(Container)：镜像中的应用程序运行后形成的进程就是容器，只是Docker会给容器做隔离，对外不可见。

#### DockerHub

> 镜像Docker托管平台。成为Docker Registry
>
> 网易云镜像、阿里云镜像库。

#### Docker架构

> CS架构：
>
> - server：Docker守护进程，负责处理Docker指令，管理镜像和容器等
> - client：通过命令或RestAPI向服务端发起指令。可以在本地或远程向服务端发送指令。

![image-20211016221211412](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016221211412.png)



## 安装Docker

### 0.安装Docker

Docker 分为 CE 和 EE 两大版本。CE 即社区版（免费，支持周期 7 个月），EE 即企业版，强调安全，付费使用，支持周期 24 个月。

Docker CE 分为 `stable` `test` 和 `nightly` 三个更新频道。

官方网站上有各种环境下的 [安装指南](https://docs.docker.com/install/)，这里主要介绍 Docker CE 在 CentOS上的安装。

### 1.CentOS安装Docker

Docker CE 支持 64 位版本 CentOS 7，并且要求内核版本不低于 3.10， CentOS 7 满足最低内核的要求，所以我们在CentOS 7安装Docker。



#### 1.1.卸载（可选）

如果之前安装过旧版本的Docker，可以使用下面命令卸载：

```
yum remove docker \
                  docker-client \
                  docker-client-latest \
                  docker-common \
                  docker-latest \
                  docker-latest-logrotate \
                  docker-logrotate \
                  docker-selinux \
                  docker-engine-selinux \
                  docker-engine \
                  docker-ce
```



#### 1.2.安装docker

首先需要大家虚拟机联网，安装yum工具

```sh
yum install -y yum-utils \
           device-mapper-persistent-data \
           lvm2 --skip-broken
```



然后更新本地镜像源：

```shell
# 设置docker镜像源
yum-config-manager \
    --add-repo \
    https://mirrors.aliyun.com/docker-ce/linux/centos/docker-ce.repo
    
sed -i 's/download.docker.com/mirrors.aliyun.com\/docker-ce/g' /etc/yum.repos.d/docker-ce.repo

yum makecache fast
```





然后输入命令：

```shell
yum install -y docker-ce
```

docker-ce为社区免费版本。稍等片刻，docker即可安装成功。



#### 1.3.启动docker

Docker应用需要用到各种端口，逐一去修改防火墙设置。非常麻烦，因此建议大家直接关闭防火墙！

启动docker前，一定要关闭防火墙后！！

启动docker前，一定要关闭防火墙后！！

启动docker前，一定要关闭防火墙后！！



```sh
# 关闭
systemctl stop firewalld
# 禁止开机启动防火墙
systemctl disable firewalld
```



通过命令启动docker：

```sh
systemctl start docker  # 启动docker服务

systemctl stop docker  # 停止docker服务

systemctl restart docker  # 重启docker服务
```



然后输入命令，可以查看docker版本：

```
docker -v
```

如图：

![image-20210418154704436](https://gitee.com/DengSchoo374/img/raw/master/img/image-20210418154704436.png) 



#### 1.4.配置镜像加速

docker官方镜像仓库网速较差，我们需要设置国内镜像服务：

参考阿里云的镜像加速文档：https://cr.console.aliyun.com/cn-hangzhou/instances/mirrors





## Docker的基本操作

### 镜像操作

- 镜像名称一般分两部分组成：[repository]:[tag]
- 没有指定tag的时候 默认是latest，代表最新版本的镜像

![image-20211016222029656](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016222029656.png)



![image-20211016222135403](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016222135403.png)

> docker --help 查看所有命令
>
> docker images --help 查看images命令

![image-20211016222349057](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016222349057.png)

![image-20211016222517769](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016222517769.png)

### 容器操作

![image-20211016222751971](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016222751971.png)

![image-20211016222942020](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016222942020.png)

> 返回容器唯一ID
>
> docker ps：查看容器运行状态
>
> ![image-20211016223050555](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016223050555.png)
>
> dcoker logs mn:查看容器名为mn的日志信息

![image-20211016223312345](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016223312345.png)

![image-20211016223637027](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016223637027.png)

![image-20211016223745712](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016223745712.png)



练习：下载redis镜像，

![image-20211016224007739](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016224007739.png)

![image-20211016224015026](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016224015026.png)



### 数据卷 Volume

#### 数据卷基本操作

> 是一个虚拟目录，指向宿主机文件系统中的某个目录。

![image-20211016224233421](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016224233421.png)

![image-20211016224433053](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016224433053.png)

> docker volume [COMMAND]
>
> - Create：创建一个Volume
> - inspect：显示一个或多个volume的信息
> - ls：列出所有的volume
> - prune：删除未使用的volume
> - rm：删除一个或多个指定的volume



![image-20211016224827132](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016224827132.png)



![image-20211016224848388](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016224848388.png)



#### 挂载数据卷

![image-20211016225013438](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016225013438.png)

![image-20211016225408884](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016225408884.png)

> ![image-20211016225450195](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016225450195.png)

#### 挂载目录

![image-20211016225652593](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016225652593.png)

#### 与数据卷挂在的方式对比



![image-20211016230232241](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016230232241.png)

![image-20211016230700183](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016230700183.png)

## Dockerfile自定义镜像

### 镜像结构

![image-20211016231007169](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016231007169.png)

![image-20211016231104052](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016231104052.png)





### DockerFile语法

> DockerFile就是一个文本文件，其中包含一个个的指令，用指令来说明执行什么操作来构建镜像。每一个指令都会形成一个layer。

![image-20211016231259083](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016231259083.png)

> 更新详细语法说明，请参考官网文档： https://docs.docker.com/engine/reference/builder



### 构建Java项目

![image-20211016231447249](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016231447249.png)





```dockerfile
# 指定基础镜像
FROM ubuntu:16.04
# 配置环境变量，JDK的安装目录
ENV JAVA_DIR=/usr/local

# 拷贝jdk和java项目的包
COPY ./jdk8.tar.gz $JAVA_DIR/
COPY ./docker-demo.jar /tmp/app.jar

# 安装JDK
RUN cd $JAVA_DIR \
 && tar -xf ./jdk8.tar.gz \
 && mv ./jdk1.8.0_144 ./java8

# 配置环境变量
ENV JAVA_HOME=$JAVA_DIR/java8
ENV PATH=$PATH:$JAVA_HOME/bin

# 暴露端口
EXPOSE 8090
# 入口，java项目的启动命令
ENTRYPOINT java -jar /tmp/app.jar
```

`docker build -t javaweb .`从当前目录构建镜像。

![image-20211016232103746](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016232103746.png)

![image-20211016232043584](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016232043584.png)

## Docker-Compose

### 初识DockerCompose

> - Docker Compose可以基于Compose文件帮我们快速的部署分布式应用。
> - Compose文件是个文件文件，通过指令定义集群中的每个容器如何运行。

![image-20211016232502312](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016232502312.png)



> DockerCompose的详细语法参考官网：https://docs.docker.com/compose/compose-file/

### 安装Docker Compose

#### 2.1.下载

Linux下需要通过命令下载：

```sh
# 安装
curl -L https://github.com/docker/compose/releases/download/1.23.1/docker-compose-`uname -s`-`uname -m` > /usr/local/bin/docker-compose
```

如果下载速度较慢，或者下载失败，可以使用课前资料提供的docker-compose文件：

![image-20210417133020614](https://gitee.com/DengSchoo374/img/raw/master/img/image-20210417133020614.png)

上传到`/usr/local/bin/`目录也可以。



#### 2.2.修改文件权限

修改文件权限：

```sh
# 修改权限 增加执行权
chmod +x /usr/local/bin/docker-compose
```





#### 2.3.Base自动补全命令：

```sh
# 补全命令
curl -L https://raw.githubusercontent.com/docker/compose/1.29.1/contrib/completion/bash/docker-compose > /etc/bash_completion.d/docker-compose
```

如果这里出现错误，需要修改自己的hosts文件：

```sh
echo "199.232.68.133 raw.githubusercontent.com" >> /etc/hosts
```



### 部署微服务集群

![image-20211016233727976](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016233727976.png)

```yaml
version: "3.2"

services:
  nacos:
    image: nacos/nacos-server
    environment:
      MODE: standalone
    ports:
      - "8848:8848"
  mysql:
    image: mysql:5.7.25
    environment:
      MYSQL_ROOT_PASSWORD: 123
    volumes:
      - "$PWD/mysql/data:/var/lib/mysql" # Pwd是打印当前目录
      - "$PWD/mysql/conf:/etc/mysql/conf.d/"
  userservice:
    build: ./user-service # 根据docker file构建
  orderservice:
    build: ./order-service
  gateway:
    build: ./gateway
    ports:
      - "10010:10010"
```



```xml
<build>
        <finalName>app</finalName>
        <plugins>
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
            </plugin>
        </plugins>
    </build>
```

`docker-compose up -d`创建并运行容器



> 需要根据需要先启动一些服务 比如nacos。
>
> `docker-compose restart gateway userservice orderservice`
>
> docker-compose顺序命令 



## Docker镜像服务

![image-20211016234247686](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016234247686.png)

### 搭建私有镜像仓库



搭建镜像仓库可以基于Docker官方提供的DockerRegistry来实现。

官网地址：https://hub.docker.com/_/registry



#### 3.1.简化版镜像仓库

Docker官方的Docker Registry是一个基础版本的Docker镜像仓库，具备仓库管理的完整功能，但是没有图形化界面。

搭建方式比较简单，命令如下：

```sh
docker run -d \
    --restart=always \
    --name registry	\
    -p 5000:5000 \
    -v registry-data:/var/lib/registry \
    registry
```



命令中挂载了一个数据卷registry-data到容器内的/var/lib/registry 目录，这是私有镜像库存放数据的目录。

访问http://YourIp:5000/v2/_catalog 可以查看当前私有镜像服务中包含的镜像



#### 3.2.带有图形化界面版本

使用DockerCompose部署带有图象界面的DockerRegistry，命令如下：

```yaml
version: '3.0'
services:
  registry:
    image: registry
    volumes:
      - ./registry-data:/var/lib/registry
  ui:
    image: joxit/docker-registry-ui:static
    ports:
      - 8080:80
    environment:
      - REGISTRY_TITLE=xxxname
      - REGISTRY_URL=http://registry:5000
    depends_on:
      - registry
```



#### 3.3.配置Docker信任地址

我们的私服采用的是http协议，默认不被Docker信任，所以需要做一个配置：

```sh
# 打开要修改的文件
vi /etc/docker/daemon.json
# 添加内容：
"insecure-registries":["http://192.168.150.101:8080"]
# 重加载
systemctl daemon-reload
# 重启docker
systemctl restart docker
```



### 向镜像仓库推送&拉取镜像

1. 重新tag本地镜像，名称前缀为私有仓库的地址

   `docker tag nginx:latest 192.168.150.101:8080/nginx:1.0`

2. 推送镜像

   `docker push 192.168.150.101:8080/nginx:1.0`

3. 拉去镜像

   `docker pull 192.168.150.101:8080/nginx:1.0`

![image-20211016234915798](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211016234915798.png)
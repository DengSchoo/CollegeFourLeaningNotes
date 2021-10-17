# RQ:RabbitMQ & Spring AMQP



## MQ介绍

![image-20211017105530741](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211017105530741.png)

### 同步通讯

> 微服务间基于Feign的调用就属于同步方法 存在一些问题。
>
> 优点：时效性强，可以立刻得到结果。

![image-20211017105809690](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211017105809690.png)

同步调用存在的问题：

![image-20211017105846757](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211017105846757.png)



### 异步通信

> 常见实现：事件驱动模式。

#### 优势一：解耦

![image-20211017110125141](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211017110125141.png)

#### 优势二：性能提升，吞吐量提升

![image-20211017110147653](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211017110147653.png)

#### 优势三：没有强依赖关系 不担心级联失败 以及 资源浪费

![image-20211017110223937](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211017110223937.png)



#### 优势四：流量消峰

![image-20211017110328071](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211017110328071.png)



![image-20211017110350850](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211017110350850.png)



### MQ常见框架

![image-20211017110719171](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211017110719171.png)

## RabbitMQ快速入门

### RabbitMQ安装

#### 1.单机部署

我们在Centos7虚拟机中使用Docker来安装。

##### 1.1.下载镜像

方式一：在线拉取

``` sh
docker pull rabbitmq:3-management
```



方式二：从本地加载

在课前资料已经提供了镜像包：

![image-20210423191210349](https://gitee.com/DengSchoo374/img/raw/master/img/image-20210423191210349.png) 

上传到虚拟机中后，使用命令加载镜像即可：

```sh
docker load -i mq.tar
```





##### 1.2.安装MQ

执行下面的命令来运行MQ容器：

```sh
docker run \
 -e RABBITMQ_DEFAULT_USER=itcast \
 -e RABBITMQ_DEFAULT_PASS=123321 \
 --name mq \
 --hostname mq1 \
 -p 15672:15672 \
 -p 5672:5672 \
 -d \
 rabbitmq:3-management
```

### RabbitMQ结构

![image-20211017111634011](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211017111634011.png)

![image-20211017111642151](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211017111642151.png)

### 消息模型

![image-20211017111816544](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211017111816544.png)



### 基本消息队列：BasicQueue

![image-20211017112828768](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211017112828768.png)

![image-20211017112852405](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211017112852405.png)

## Spring AMQP

### 什么是Spring AMQP

> SpringAmqp的官方地址：https://spring.io/projects/spring-amqp

![image-20211017231958399](https://gitee.com/DengSchoo374/img/raw/master/img/image-20211017231958399.png)

### Basic Queue简单队列模型



### Work Queue工作队列



### 发布、订阅模型-Fanout



### 发布、订阅模型-Topic



### 消息转发器


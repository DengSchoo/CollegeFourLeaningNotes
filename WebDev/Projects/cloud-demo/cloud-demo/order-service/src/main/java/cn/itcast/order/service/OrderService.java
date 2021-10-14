package cn.itcast.order.service;

import cn.itcast.order.clients.UserClient;
import cn.itcast.order.mapper.OrderMapper;
import cn.itcast.order.pojo.Order;
import com.deng.pojo.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class OrderService {

    @Autowired
    private OrderMapper orderMapper;
//    @Autowired
//    private RestTemplate restTemplate;

    @Autowired
    private UserClient userClient;


    public Order queryOrderById(Long orderId) {
        // 1.查询订单
        Order order = orderMapper.findById(orderId);
        // 2.利用RestTemplate发起请求
        // 2.1 url路径
        //String url = "http://localhost:8081/user/" + order.getUserId();
        //String url = "http://user-service/user/" + order.getUserId();
        // 2.2 发起http请求 实现远程调用
        //User user = restTemplate.getForObject(url, User.class);
        // 3 封装user到Order
        //order.setUser(user);

        // 4.返回


        // 使用feign远程调用
        User user = userClient.findById(order.getUserId());

        order.setUser(user);
        return order;
    }
}

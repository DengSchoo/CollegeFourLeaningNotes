package cn.itcast.order.service;

import cn.itcast.order.mapper.OrderMapper;
import cn.itcast.order.pojo.Order;
import cn.itcast.order.pojo.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

@Service
public class OrderService {

    @Autowired
    private OrderMapper orderMapper;
    @Autowired
    private RestTemplate restTemplate;

    /**
     * @author      : DengSchoo
     * @description : TODO
     * @dateTime    : 2021/10/12 16:55
     * @params      :  * @Param: null
     * @return      : 
     */
    public Order queryOrderById(Long orderId) {
        // 1.查询订单
        Order order = orderMapper.findById(orderId);
        // 2.利用RestTemplate发起请求
        // 2.1 url路径
        //String url = "http://localhost:8081/user/" + order.getUserId();
        String url = "http://user-service/user/" + order.getUserId();
        // 2.2 发起http请求 实现远程调用
        User user = restTemplate.getForObject(url, User.class);
        // 3 封装user到Order
        order.setUser(user);

        // 4.返回
        return order;
    }
}

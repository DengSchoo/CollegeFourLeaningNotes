package com.deng.gateway;

import org.springframework.cloud.gateway.filter.GatewayFilterChain;
import org.springframework.cloud.gateway.filter.GlobalFilter;
import org.springframework.core.annotation.Order;
import org.springframework.http.HttpStatus;
import org.springframework.http.server.reactive.ServerHttpRequest;
import org.springframework.stereotype.Component;
import org.springframework.util.MultiValueMap;
import org.springframework.web.server.ServerWebExchange;
import reactor.core.publisher.Mono;

/**
 * @author :Deng Schoo
 * @version :V1.0
 * @className :AuthorizeFilter
 * @description :TODO
 * @date :2021/10/15 22:25
 */

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

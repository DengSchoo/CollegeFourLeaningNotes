package com.deng.config;

import lombok.Data;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Component;

/**
 * @author :Deng Schoo
 * @version :V1.0
 * @className :PatternProperties
 * @description :TODO
 * @date :2021/10/14 20:37
 */
@Data
@Component
@ConfigurationProperties(prefix = "pattern")
public class PatternProperties {
    private String dateformat;
}

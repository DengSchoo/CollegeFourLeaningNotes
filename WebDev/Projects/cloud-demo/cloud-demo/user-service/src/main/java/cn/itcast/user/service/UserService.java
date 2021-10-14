package cn.itcast.user.service;

import cn.itcast.user.mapper.UserMapper;
import cn.itcast.user.pojo.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class UserService {

    @Autowired
    private UserMapper userMapper;

    /**
     * @author      : DengSchoo
     * @description : TODO
     * @dateTime    : 2021/10/12 18:12
     * @params
     	* @param0	: id	[java.lang.Long]
    	* @param1	: id2	[long]
     * @return      : cn.itcast.user.pojo.User
     */
    public User queryById(Long id, long id2) {
        return userMapper.findById(id);
    }
}
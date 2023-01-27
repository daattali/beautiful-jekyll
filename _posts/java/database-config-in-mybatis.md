---
title: mybatis单数据源和多数据源不同配置方式
date: 2018-05-24 15:46:38
updated: 2018-05-24 15:46:38
tags: ['mybatis配置','mybatis多数据源']
categories: 
 - 开发语言
 - Java
---

百度一下！到处都是mybatis跟spring结合的配置，可是我不想用spring来写测试代码！废话不多说，贴配置跟代码，以及测试方法。**记录一下，也方便他人，欢迎交流。**

> dao类和mapper.xml都跟mybatis平常使用的一样，都可以自动生成


# 单数据源

## 配置文件
放置在resources目录下
```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE configuration PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
    <typeAliases>
        <typeAlias alias="UserInfo" type="com.ppmon.fund.models.UserInfo" />
    </typeAliases>

    <environments default="CONFIG">
        <environment id="CONFIG">
            <transactionManager type="JDBC" />
            <dataSource type="POOLED">
                <!-- 这里填写数据库的配置 -->
                <property name="driver" value="com.mysql.cj.jdbc.Driver" />
                <property name="url" value="jdbc:mysql://192.168.1.1:3306/database?useSSL=false" />
                <property name="username" value="root" />
                <property name="password" value="root" />
            </dataSource>
        </environment>
     </environments>

    <mappers>
        <!-- 这里填写mybatis的mapperXml路径 是以classpath做为根目录的 -->
        <mapper resource="mapperXml/UserInfoMapper.xml" />
    </mappers>
</configuration>
```

## sqlSession工厂方法

```java
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.Reader;

/**
 * @author chenjun
 *
 * mybatis 获取sqlSession类
 */
public class MbSqlSessionFactory {

    private static SqlSessionFactory sqlSessionFactory;
    private static Reader reader;

    static {

        try{
            // 这里的配置文件与上面的对应
            reader = Resources.getResourceAsReader("mybatisConfig.xml");
            sqlSessionFactory = new SqlSessionFactoryBuilder().build(reader);
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    public static SqlSessionFactory getSession(){
        return sqlSessionFactory;
    }

}
```

## 测试

```java
UserInfoMapper userInfoMapper = session.getMapper(UserInfoMapper.class);
UserInfo userInfo = userInfoMapper.selectByPrimaryKey(userNo);
log.info(userInfo.toString());
```

# 多数据源

## 配置文件

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE configuration PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
    <typeAliases>
        <typeAlias alias="UserInfo" type="com.ppmon.fund.models.UserInfo" />
    </typeAliases>

    <environments default="CONFIG">
        <environment id="CONFIG">
            <transactionManager type="JDBC" />
            <dataSource type="POOLED">
                <property name="driver" value="com.mysql.cj.jdbc.Driver" />
                <property name="url" value="jdbc:mysql://192.168.1.1:3306/database1?useSSL=false" />
                <property name="username" value="root" />
                <property name="password" value="J.d@123456" />
            </dataSource>
        </environment>
        <environment id="YZD">
            <transactionManager type="JDBC" />
            <dataSource type="POOLED">
                <property name="driver" value="com.mysql.cj.jdbc.Driver" />
                <property name="url" value="jdbc:mysql://192.168.1.2:3306/database2?useSSL=false" />
                <property name="username" value="root" />
                <property name="password" value="J.d@123456" />
            </dataSource>
        </environment>
    </environments>

    <mappers>
        <!-- 这里填写mybatis的mapperXml路径 -->
        <mapper resource="mapperXml/UserInfoMapper.xml" />
    </mappers>
</configuration>
```

## sql工厂方法

```java
import lombok.extern.slf4j.Slf4j;
import org.apache.commons.io.IOUtils;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

@Slf4j
public final class MSqlSessionFactory {

    private static final String CONFIGURATION_PATH = "mybatisConfig.xml";
    private static final Map<String, org.apache.ibatis.session.SqlSessionFactory> SQLSESSIONFACTORYS = new HashMap();

    /**
     * 根据指定的DataSourceEnvironment获取对应的SqlSessionFactory 
     */
    public static SqlSessionFactory getSqlSessionFactory(String datasource) {

        SqlSessionFactory sqlSessionFactory = SQLSESSIONFACTORYS.get(datasource);
        if (!Objects.isNull(sqlSessionFactory)) {
            return sqlSessionFactory;
        } else {
            InputStream inputStream = null;
            try {
                inputStream = Resources.getResourceAsStream(CONFIGURATION_PATH);
                sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream, datasource);


                log.info("Get {} MSqlSessionFactory successfully.", datasource);
            } catch (IOException e) {
                log.warn("Get {} MSqlSessionFactory error.", datasource);
                log.error(e.getMessage(), e);
            } finally {
                IOUtils.closeQuietly(inputStream);
            }


            SQLSESSIONFACTORYS.put(datasource, sqlSessionFactory);
            return sqlSessionFactory;
        }
    }
}  
```

```java
import com.ppmon.fund.dao.Mapper;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

/**
 * MapperFactory 创建一个Mapper实例 mapper
 */
public final class MapperFactory {
    private static final org.slf4j.Logger logger = org.slf4j.LoggerFactory.getLogger(MapperFactory.class);

    /**
     * 通过datasource 创建一个Mapper 的实现类 mapper
     */
    @SuppressWarnings("unchecked")
    public static <T> T createMapper(Class<? extends Mapper> clazz, String datasource) {
        SqlSessionFactory sqlSessionFactory = getSqlSessionFactory(datasource);
        SqlSession sqlSession = sqlSessionFactory.openSession();
        Mapper mapper = sqlSession.getMapper(clazz);
        return (T) MapperProxy.bind(mapper, sqlSession);
    }

    /**
     * Mapper代理: 执行 mapper 方法和关闭 sqlSession
     */
    private static class MapperProxy implements InvocationHandler {
        private Mapper mapper;
        private SqlSession sqlSession;

        private MapperProxy(Mapper mapper, SqlSession sqlSession) {
            this.mapper = mapper;
            this.sqlSession = sqlSession;
        }

        @SuppressWarnings("unchecked")
        private static Mapper bind(Mapper mapper, SqlSession sqlSession) {
            return (Mapper) Proxy.newProxyInstance(mapper.getClass().getClassLoader(),
                    mapper.getClass().getInterfaces(), new MapperProxy(mapper, sqlSession));
        }

        /**
         * 执行mapper方法并最终关闭sqlSession
         */
        @Override
        public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
            Object object = null;
            try {
                object = method.invoke(mapper, args);
            } catch (Exception e) {
                e.printStackTrace();
                logger.error(e.getMessage(), e);
            } finally {
                sqlSession.close();
            }
            return object;
        }
    }

    /**
     * 获取数据源 datasource 的 MSqlSessionFactory
     */
    private static SqlSessionFactory getSqlSessionFactory(String datasource) {
        return MSqlSessionFactory.getSqlSessionFactory(datasource);
    }
}
```

注意：所有的dao类都要继承Mapper接口

```java
public interface Mapper {
}
```

```java
public interface UserInfoMapper extends Mapper{
    UserInfo selectByPrimaryKey(Long id);
}
```

## 测试

```java
// 第二个参数传的便是mybatisConfig.xml里面配置的environment id
UserInfoMapper userInfoMapper = MapperFactory.createMapper(UserInfoMapper.class, "CONFIG");
UserInfo userInfo = userInfoMapper.selectByPrimaryKey(userNo);
log.info(userInfo.toString());
```

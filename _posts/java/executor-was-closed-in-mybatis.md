---
title: Cause org.apache.ibatis.executor.ExecutorException Executor was closed
date: 2018-05-30 17:25:08
tags: ['mybatis']
categories: 
 - 开发语言
 - Java
---

# 背景

只使用了mybatis未使用spring，因为涉及多数据源，所以每次查询都是通过mapper工厂方法来创建mapper在执行select或着Update。
同一个mapper执行完select在执行update便报错 Executor was closed 。

# 解决

看日志

```log
2018-05-30 17:09:58,941 DEBUG [org.apache.ibatis.transaction.jdbc.JdbcTransaction] - Closing JDBC Connection [com.mysql.cj.jdbc.ConnectionImpl@2a9650c7]
2018-05-30 17:09:58,941 DEBUG [org.apache.ibatis.datasource.pooled.PooledDataSource] - Returned connection 714494151 to pool.
```

可以看出连接在执行完查询后便`归还`给了连接池，再次使用查询便会报错咯。

目前我的做法是查询创建一次连接，然后执行update前又创建一次连接，搞定。

```
ChannelsInstallmentLederMapper channelsInstallmentLederMapper = MapperFactory.createMapper(ChannelsInstallmentLederMapper.class, (String) Constant.DATA_SOURCE.get(dataSource));

// 查询
List<ChannelsInstallmentLeder> channelsInstallmentLeders = channelsInstallmentLederMapper.selectByOrderIdAndPeriod(orderId, period);

// 更新
for (ChannelsInstallmentLeder channelsInstallmentLeder:channelsInstallmentLeders) {
            channelsInstallmentLederMapper = MapperFactory.createMapper(ChannelsInstallmentLederMapper.class, (String) Constant.DATA_SOURCE.get(dataSource));
            channelsInstallmentLeder.setCollectdate(new Date());
            channelsInstallmentLederMapper.updateByPrimaryKey(channelsInstallmentLeder);
        }
```

```
2018-05-30 17:09:58,941 DEBUG [org.apache.ibatis.transaction.jdbc.JdbcTransaction] - Closing JDBC Connection [com.mysql.cj.jdbc.ConnectionImpl@2a9650c7]
2018-05-30 17:09:58,941 DEBUG [org.apache.ibatis.datasource.pooled.PooledDataSource] - Returned connection 714494151 to pool.
2018-05-30 17:09:58,941 DEBUG [org.apache.ibatis.transaction.jdbc.JdbcTransaction] - Opening JDBC Connection
2018-05-30 17:09:58,941 DEBUG [org.apache.ibatis.datasource.pooled.PooledDataSource] - Checked out connection 714494151 from pool.
```

**若您有更好的方法还望不吝赐教**
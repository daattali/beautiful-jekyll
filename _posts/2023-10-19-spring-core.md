## srping-core

### 1. Ioc容器

#### 1.1. Spring IoC容器和Bean简介

- ApplicationContext 是 BeanFactory 的一个子接口。

- BeanFactory 提供了配置框架和基本功能，而 ApplicationContext 则增加了更多的企业特定功能。

- ApplicationContext 是 BeanFactory 的一个完整的超集。

#### 1.2.容器概述

- `ApplicationContext` 接口代表Spring IoC容器，负责实例化、配置和组装bean。

- 常见的有ClassPathXmlApplicationContext 或 FileSystemXmlApplicationContext。

##### 1.2.1. 配置元数据

- XML，基于注解的配置，Java-based configuration

#####  1.2.2. 实例化一个容器

```java
ApplicationContext context = new ClassPathXmlApplicationContext("services.xml", "daos.xml");
```

##### 构建基于XML的配置元数据

```xml
<beans>
    <import resource="services.xml"/>
    <import resource="resources/messageSource.xml"/><!-- 不推荐 -->
    <import resource="/resources/themeSource.xml"/><!-- 不推荐 -->

    <bean id="bean1" class="..."/>
    <bean id="bean2" class="..."/>
</beans>
```

##### 1.2.3. 使用容器

```java
// 创建和配置bean
ApplicationContext context = new ClassPathXmlApplicationContext("services.xml", "daos.xml");

// 检索配置的实例
//不推荐，直接用autowired
PetStoreService service = context.getBean("petStore", PetStoreService.class);

// 使用配置的实例
List<String> userList = service.getUsernameList();
```

```java
GenericApplicationContext context = new GenericApplicationContext();
new XmlBeanDefinitionReader(context).loadBeanDefinitions("services.xml", "daos.xml");
context.refresh();
```

#### 1.3. Bean 概览

- 在容器本身中，这些Bean定义被表示为 `BeanDefinition` 对象，这些Bean是用你提供给容器的配置元数据创建的。
- 也可以通过 `getBeanFactory()` 方法访问 `ApplicationContext` 的 `BeanFactory` 来实现的，该方法返回 `DefaultListableBeanFactory` 实现。`DefaultListableBeanFactory` 通过 `registerSingleton(..)` 和 `registerBeanDefinition(..)` 方法支持这种注册（不推荐）。

##### 1.3.1. Bean 命名

- 一个Bean通常只有一个标识符。然而，如果它需要一个以上的标识符，多余的标识符可以被视为别名。
- 在基于XML的配置元数据中，你可以使用 `id` 属性、`name` 属性或两者来指定Bean标识符
- 如果你想为Bean引入其他别名，你也可以在 `name` 属性中指定它们，用逗号（`,`）、分号（`;`）或空格分隔。
- 如果你不明确地提供 `name` 或 `id`，容器将为该 Bean 生成一个唯一的名称。
- 惯例是在命名Bean时使用标准的Java惯例来命名实例字段名。也就是说，Bean的名字以小写字母开始，然后以驼峰字母开头。这种名称的例子包括 `accountManager`、`accountService`、`userDao`、`loginController` 等等。

###### 在 Bean Definition 之外对Bean进行别名

```xml
<alias name="fromName" alias="toName"/>
```

##### 1.3.2. 实例化 Bean

- 嵌套类名：Bean定义中的 `class` 属性的值将是 `com.example.SomeThing$OtherThing` 或 `com.example.SomeThing.OtherThing`

###### 用构造函数进行实例化

需要一个默认（空）构造函数。

###### 用静态工厂方法进行实例化

```java
public class ClientService {
    private static ClientService clientService = new ClientService();
    private ClientService() {}

    public static ClientService createInstance() {
        return clientService;
    }
}
```

###### 用实例工厂方法进行实例化

```java
public class DefaultServiceLocator {

    private static ClientService clientService = new ClientServiceImpl();

    public ClientService createClientServiceInstance() {
        return clientService;
    }
}
```

###### 确定Bean的运行时类型

工厂方法返回的对象和工厂方法bean的运行时类型不一样。要了解某个特定Bean的实际运行时类型，推荐的方法是对指定的Bean名称进行 `BeanFactory.getType` 调用。

#### 1.4. 依赖

##### 1.4.1. 依赖注入

###### 基于构造器的依赖注入

默认构造函数参数解析匹配是通过使用参数的类型进行的

~~~xml
         ```
         <!--按顺序进行构造 -->
         <bean id="exampleBean" class="examples.ExampleBean">
             <constructor-arg index="0" value="7500000"/>
             <constructor-arg index="1" value="42"/>
         </bean>
         ```
~~~
```xml
         <!--按类型进行构造。构造器类型唯一时 -->
         <bean id="exampleBean" class="examples.ExampleBean">
             <constructor-arg type="int" value="7500000"/>
             <constructor-arg type="java.lang.String" value="42"/>
         </bean>
```

~~~xml
     ```
     <!--按参数名称进行构造。name为参数名称 -->
     <bean id="exampleBean" class="examples.ExampleBean">
         <constructor-arg name="years" value="7500000"/>
         <constructor-arg name="ultimateAnswer" value="42"/>
     </bean>
     ```
~~~
~~~xml
 ```
 <!--引用其他bean构造。beanTwo和beanThree没有继承关系 -->
 <beans>
     <bean id="beanOne" class="x.y.ThingOne">
         <constructor-arg ref="beanTwo"/>
         <constructor-arg ref="beanThree"/>
     </bean>
 
     <bean id="beanTwo" class="x.y.ThingTwo"/>
 
     <bean id="beanThree" class="x.y.ThingThree"/>
 </beans>
 ```
~~~
```java
 package examples;
 
 public class ExampleBean {
 
     // Fields omitted
 
     @ConstructorProperties({"years", "ultimateAnswer"})
     public ExampleBean(int years, String ultimateAnswer) {
         this.years = years;
         this.ultimateAnswer = ultimateAnswer;
     }
 }
```

###### 基于Setter的依赖注入

```java
public class SimpleMovieLister {

    // the SimpleMovieLister has a dependency on the MovieFinder
    private MovieFinder movieFinder;

    // a setter method so that the Spring container can inject a MovieFinder
    //在xml写相关的movieFinder的信息
    public void setMovieFinder(MovieFinder movieFinder) {
        this.movieFinder = movieFinder;
    }

    // business logic that actually uses the injected MovieFinder is omitted...
}
```

- 一个好的经验法则是对强制依赖使用构造函数，对可选依赖使用setter方法或配置方法。

- Spring团队通常提倡构造函数注入，因为它可以注入的对象不会被调用setter方法改变（也是setter的优点，可以重复注入）。

- Setter注入主要应该只用于在类中可以分配合理默认值的可选依赖。否则，必须在代码使用依赖的所有地方进行非null值检查。

###### 依赖解析过程

- 当容器被创建时，那些具有单例作用域并被设置为预实例化的Bean（默认）被创建。作用域在 [Bean Scope](https://springdoc.cn/spring/core.html#beans-factory-scopes) 中定义。否则，Bean只有在被请求时才会被创建。

###### 依赖注入例子

- 略

##### 1.4.2. 依赖和配置的细节

###### 字面值 (基本类型、 String 等)

```xml
<bean id="myDataSource" class="org.apache.commons.dbcp.BasicDataSource" destroy-method="close">
    <!-- results in a setDriverClassName(String) call -->
    <property name="driverClassName" value="com.mysql.jdbc.Driver"/>
    <property name="url" value="jdbc:mysql://localhost:3306/mydb"/>
    <property name="username" value="root"/>
    <property name="password" value="misterkaoli"/>
</bean>
```



###### 对其他Bean的引用（合作者）

- 被引用的 bean 是其属性要被设置的 bean 的依赖关系，它在属性被设置之前根据需要被初始化。

- 通过 `<ref/>` 标签的 `bean` 属性指定目标 bean 是最一般的形式，它允许创建对同一容器或父容器中的任何 bean 的引用，不管它是否在同一个 XML 文件中。`bean` 属性的值可以与目标bean的 `id` 属性相同，或者与目标bean的 `name` 属性中的一个值相同。

  ```xml
  <ref bean="someBean"/>
  ```

  ```xml
  <!-- in the parent context -->
  <bean id="accountService" class="com.something.SimpleAccountService">
      <!-- insert dependencies as required here -->
  </bean>
  <!-- parent context end-->
  
  <!-- in the child (descendant) context -->
  <bean id="accountService" <!-- bean name is the same as the parent bean -->
      class="org.springframework.aop.framework.ProxyFactoryBean">
      <property name="target">
          <ref parent="accountService"/> <!-- notice how we refer to the parent bean -->
      </property>
      <!-- insert other configuration and dependencies as required here -->
  </bean>
  ```

  

###### 内部 Bean

```xml
<bean id="outer" class="...">
    <!-- 而不是使用对目标Bean的引用，只需在行内定义目标Bean即可 -->
    <property name="target">
        <bean class="com.example.Person"> <!-- 这是内部Bean -->
            <property name="name" value="Fiona Apple"/>
            <property name="age" value="25"/>
        </bean>
    </property>
</bean>
```



###### 集合（Collection）

- `<list/>`、`<set/>`、`<map/>` 和 `<props/>` 元素分别设置Java `Collection` 类型 `List`、`Set`、`Map` 和 `Properties` 的属性和参数。

```xml
<bean id="moreComplexObject" class="example.ComplexObject">
    <!-- results in a setAdminEmails(java.util.Properties) call -->
    <property name="adminEmails">
        <props>
            <prop key="administrator">administrator@example.org</prop>
            <prop key="support">support@example.org</prop>
            <prop key="development">development@example.org</prop>
        </props>
    </property>
    <!-- results in a setSomeList(java.util.List) call -->
    <property name="someList">
        <list>
            <value>a list element followed by a reference</value>
            <ref bean="myDataSource" />
        </list>
    </property>
    <!-- results in a setSomeMap(java.util.Map) call -->
    <property name="someMap">
        <map>
            <entry key="an entry" value="just some string"/>
            <entry key="a ref" value-ref="myDataSource"/>
        </map>
    </property>
    <!-- results in a setSomeSet(java.util.Set) call -->
    <property name="someSet">
        <set>
            <value>just some string</value>
            <ref bean="myDataSource" />
        </set>
    </property>
</bean>
```

map的key值或value值，或set值，也可以是以下任何元素。

```xml
bean | ref | idref | list | set | map | props | value | null
```

- Spring容器也支持合并集合。开发者可以定义一个父 `<list/>`、`<map/>`、`<set/>` 或` <props/> `元素，让子` <list/>`、`<map/>`、`<set/> `或` <props/> `元素继承和覆盖父集合的值。在 `<list/>` 元素的特殊情况下，与 `List` 集合类型相关的语义（也就是值的有序集合的概念）被保持。不能合并不同的集合类型（例如 `Map` 和 `List`）。

```xml
<beans>
    <bean id="parent" abstract="true" class="example.ComplexObject">
        <property name="adminEmails">
            <props>
                <prop key="administrator">administrator@example.com</prop>
                <prop key="support">support@example.com</prop>
            </props>
        </property>
    </bean>
    <bean id="child" parent="parent">
        <property name="adminEmails">
            <!-- the merge is specified on the child collection definition -->
            <props merge="true">
                <prop key="sales">sales@example.com</prop>
                <prop key="support">support@example.co.uk</prop>
            </props>
        </property>
    </bean>
<beans>
```



###### Null and Empty String Values

```xml
<bean class="ExampleBean">
    <property name="email" value=""/>
</bean>
<bean class="ExampleBean2">
    <property name="email">
        <null/>
    </property>
</bean>
```



###### 使用p命名空间的XML快捷方式

略

###### 使用c命名空间的XML快捷方式

略

###### 复合属性名

##### 1.4.3. 使用 depends-on

- `depends-on` 属性可以明确地强制一个或多个Bean在使用此元素的Bean被初始化之前被初始化。

- 在单例Bean的情况下，也可以指定相应的销毁时间的依赖关系。与给定Bean定义了 `depends-on` 的依赖Bean会在给定Bean本身被销毁之前被首先销毁

  ```xml
  <bean id="beanOne" class="ExampleBean" depends-on="manager,accountDao">
      <property name="manager" ref="manager" />
  </bean>
  
  <bean id="manager" class="ManagerBean" />
  <bean id="accountDao" class="x.y.jdbc.JdbcAccountDao" />
  ```

##### 1.4.4. 懒加载的Bean

- 懒加载的 bean 告诉IoC容器在第一次被请求时创建一个bean实例，而不是在启动时。

- 可以通过使用 `<beans/>` 元素上的 `default-lazy-init` 属性来控制容器级的懒加载

  ```xml
  
  <beans default-lazy-init="true">
      <!-- no beans will be pre-instantiated... -->
      <bean id="lazy" class="com.something.ExpensiveToCreateBean" lazy-init="true"/>
  	<bean name="not.lazy" class="com.something.AnotherBean"/>
  </beans>
  ```

##### 1.4.5. 注入协作者（Autowiring Collaborators）

- 当使用基于XML的配置元数据时，你可以用 `<bean/>` 元素的 `autowire` 属性来指定bean定义的自动注入模式。

  | 模式          | 解释                                                         |
  | :------------ | :----------------------------------------------------------- |
  | `no`          | （默认）没有自动注入。Bean引用必须由 `ref` 元素来定义。对于大型部署来说，不建议改变默认设置，因为明确指定协作者会带来更大的控制力和清晰度。在某种程度上，它记录了一个系统的结构。 |
  | `byName`      | 通过属性名称进行自动注入。Spring寻找一个与需要自动注入的属性同名的Bean。例如，如果一个Bean定义被设置为按名称自动注入，并且它包含一个 `master` 属性（也就是说，它有一个 `setMaster(..)` 方法），Spring会寻找一个名为 `master` 的Bean定义并使用它来设置该属性。 |
  | `byType`      | 如果容器中正好有一个 property 类型的 bean 存在，就可以自动注入该属性。如果存在一个以上的bean，就会抛出一个致命的 exception，这表明你不能对该bean使用 `byType` 自动注入。如果没有匹配的 bean，就不会发生任何事情（该属性没有被设置）。 |
  | `constructor` | 类似于 `byType`，但适用于构造函数参数。如果容器中没有一个构造函数参数类型的bean，就会产生一个致命的错误。 |

###### 从自动注入中排除一个Bean

- 在Spring的XML格式中，将 `<bean/>` 元素的 `autowire-candidate` 属性设置为 `false`。`autowire-candidate` 属性被设计为只影响基于类型的自动注入。

##### 1.4.6. 方法注入

###### 查找方法依赖注入

```xml
<!-- a stateful bean deployed as a prototype (non-singleton) -->
<bean id="myCommand" class="fiona.apple.AsyncCommand" scope="prototype">
    <!-- inject dependencies here as required -->
</bean>

<!-- commandProcessor uses statefulCommandHelper -->
<bean id="commandManager" class="fiona.apple.CommandManager">
    <lookup-method name="createCommand" bean="myCommand"/>
</bean>
```

###### 任意方法替换

- 方法注入的一个不太有用的形式是用另一个方法实现替换托管Bean中的任意方法的能力

  ```xml
  <bean id="myValueCalculator" class="x.y.z.MyValueCalculator">
      <!-- arbitrary method replacement -->
      <replaced-method name="computeValue" replacer="replacementComputeValue">
          <arg-type>String</arg-type>
      </replaced-method>
  </bean>
  
  <bean id="replacementComputeValue" class="a.b.c.ReplacementComputeValue"/>
  ```

#### 1.5. Bean Scope

| Scope                                                        | 说明                                                         |
| :----------------------------------------------------------- | :----------------------------------------------------------- |
| [singleton](https://springdoc.cn/spring/core.html#beans-factory-scopes-singleton) | （默认情况下）为每个Spring IoC容器将单个Bean定义的Scope扩大到单个对象实例。 |
| [prototype](https://springdoc.cn/spring/core.html#beans-factory-scopes-prototype) | 将单个Bean定义的Scope扩大到任何数量的对象实例。              |
| [request](https://springdoc.cn/spring/core.html#beans-factory-scopes-request) | 将单个Bean定义的Scope扩大到单个HTTP请求的生命周期。也就是说，每个HTTP请求都有自己的Bean实例，该实例是在单个Bean定义的基础上创建的。只在Web感知的Spring `ApplicationContext` 的上下文中有效。 |
| [session](https://springdoc.cn/spring/core.html#beans-factory-scopes-session) | 将单个Bean定义的Scope扩大到一个HTTP `Session` 的生命周期。只在Web感知的Spring `ApplicationContext` 的上下文中有效。 |
| [application](https://springdoc.cn/spring/core.html#beans-factory-scopes-application) | 将单个Bean定义的 Scope 扩大到 `ServletContext` 的生命周期中。只在Web感知的Spring `ApplicationContext` 的上下文中有效。 |
| [websocket](https://springdoc.cn/spring/web.html#websocket-stomp-websocket-scope) | 将单个Bean定义的 Scope 扩大到 `WebSocket` 的生命周期。仅在具有Web感知的 Spring `ApplicationContext` 的上下文中有效。 |

##### 1.5.1. Singleton Scope

- 只有一个单例 Bean 的共享实例被管理，所有对具有符合该Bean定义的ID的Bean的请求都会被Spring容器返回该特定的Bean实例。

##### 1.5.2. Prototype Scope

- Bean 部署的 prototype scope 导致每次对该特定Bean的请求都会创建一个新的Bean实例。

##### 1.5.3. singleton Bean 和 prototype bean 依赖

- 请注意依赖关系是在实例化时解析的

##### 1.5.4. Request、 Session、 Application 和 WebSocket Scope

###### 初始 Web 配置

- 在Spring Web MVC中访问 scope 内的Bean，实际上是在一个由Spring `DispatcherServlet` 处理的请求（request）中，就不需要进行特别的设置。 `DispatcherServlet` 已经暴露了所有相关的状态。
- 

###### Request scope

```xml
<bean id="loginAction" class="com.something.LoginAction" scope="request"/>
```

###### Session Scope

```xml
<bean id="userPreferences" class="com.something.UserPreferences" scope="session"/>
```

###### Application Scope

```xml
<bean id="appPreferences" class="com.something.AppPreferences" scope="application"/>
```

###### WebSocket Scope

略

###### 作为依赖的 Scope Bean

- 使用代理

```xml
<bean id="userPreferences" class="com.something.UserPreferences" scope="session">
    <aop:scoped-proxy/>
</bean>

<bean id="userManager" class="com.something.UserManager">
    <property name="userPreferences" ref="userPreferences"/>
</bean>
```

##### 1.5.5. 自定义 Scope**没看懂**

###### 创建自定义 Scope

- 需要实现 `org.springframework.beans.factory.config.Scope` 接口

  ```java
  Object get(String name, ObjectFactory<?> objectFactory)
  Object remove(String name)
  void registerDestructionCallback(String name, Runnable destructionCallback)
  String getConversationId()
  ```

###### 使用自定义 Scope

```java
Scope threadScope = new SimpleThreadScope();
beanFactory.registerScope("thread", threadScope);
```

```xml
    <bean class="org.springframework.beans.factory.config.CustomScopeConfigurer">
        <property name="scopes">
            <map>
                <entry key="thread">
                    <bean class="org.springframework.context.support.SimpleThreadScope"/>
                </entry>
            </map>
        </property>
    </bean>
```

#### 1.6. 自定义Bean的性质（Nature）

##### 1.6.1. 生命周期回调

###### 初始化回调

- 实现 `InitializingBean` 接口（不推荐）

- ```xml
  <bean id="exampleInitBean" class="examples.ExampleBean" init-method="init"/>
  ```

- 使用 `@PostConstruct` 注解

###### 销毁回调

- 使用 `DisposableBean` 回调接口（不推荐）

- ```xml
  <bean id="exampleInitBean" class="examples.ExampleBean" destroy-method="cleanup"/>
  ```

- 使用 `@PreDestroy` 注解

###### 默认的初始化和销毁方法

```xml
<beans default-init-method="init" default-destroy-method="destory">

    <bean id="blogService" class="com.something.DefaultBlogService">
        <property name="blogDao" ref="blogDao" />
    </bean>

</beans>
```

###### 结合生命周期机制（执行顺序）

- @PostConstruct
- InitializingBean.afterPropertiesSet()
- init()
- @PreDestroy
- DisposableBean.destroy()
- destroy()

###### 启动和关闭的回调

- 有时候，直接的依赖关系是未知的。你可能只知道某种类型的对象应该在另一种类型的对象之前启动。在这些情况下， `SmartLifecycle` 接口定义了另一个选项，即其超接口 `Phased` 上定义的 `getPhase()` 方法。启动时，phase最低的对象先启动。当停止时，phase最高的对象先停止。

###### 在非Web应用中优雅地关闭Spring IoC容器

```xml
public final class Boot {

    public static void main(final String[] args) throws Exception {
        ConfigurableApplicationContext ctx = new ClassPathXmlApplicationContext("beans.xml");

        // add a shutdown hook for the above context...
        ctx.registerShutdownHook();

        // app runs here...

        // main method exits, hook is called prior to the app shutting down...
    }
}
```

###### ApplicationContextAware 和 BeanNameAware

- 当 `ApplicationContext` 创建一个实现 `org.springframework.context.ApplicationContextAware` 接口的对象实例时，该实例被提供给该 `ApplicationContext` 的引用。(不推荐)
- Autowire 是获得对 `ApplicationContext` 引用的另一种选择。
- 当 `ApplicationContext` 创建一个实现 `org.springframework.beans.factory.BeanNameAware` 接口的类时，该类被提供给其相关对象定义中定义的名称的引用。

###### 其他 Aware 接口

| 接口名称                         | 注入的依赖性                                                 |
| :------------------------------- | :----------------------------------------------------------- |
| `ApplicationContextAware`        | 声明 `ApplicationContext`。                                  |
| `ApplicationEventPublisherAware` | 封装了 `ApplicationContext` 的 Event publisher 。            |
| `BeanClassLoaderAware`           | 用来加载Bean类的类加载器（Class loader）。                   |
| `BeanFactoryAware`               | 声明 `BeanFactory`。                                         |
| `BeanNameAware`                  | 声明Bean的名称。                                             |
| `LoadTimeWeaverAware`            | 定义了用于在加载时处理类定义的织入点。                       |
| `MessageSourceAware`             | 配置解析消息的策略（支持参数化和国际化）。                   |
| `NotificationPublisherAware`     | Spring JMX notification publisher。                          |
| `ResourceLoaderAware`            | 配置的加载器用于低级别的资源访问。                           |
| `ServletConfigAware`             | 容器所运行的当前 `ServletConfig`。仅在 Web 感知的 Spring `ApplicationContext` 中有效。 |

#### 1.7. Bean 定义（Definition）的继承

```xml
<bean id="inheritedTestBean" abstract="true">
    <property name="name" value="parent"/>
    <property name="age" value="1"/>
</bean>

<bean id="inheritsWithDifferentClass"
        class="org.springframework.beans.DerivedTestBean"
        parent="inheritedTestBean" init-method="initialize">  
    <property name="name" value="override"/>
    <!-- the age property value of 1 will be inherited from parent -->
</bean>
```

- 子Bean定义会使用父定义中的Bean类，但也可以覆盖它（覆盖时子Bean类必须与父类兼容）。
- 子Bean定义从父级继承scope、构造函数参数值、属性值和方法重写，并可以选择添加新的值。
- 其余的设置总是来自于子定义：依赖、自动注入模式、依赖检查、singleton和懒加载。
- 如果父定义没有指定一个类，就需要明确地将父Bean定义标记为 `abstract` 。当一个定义是 `abstract` 的，它只能作为一个纯模板Bean定义使用，作为子定义的父定义。

#### 1.8. 容器扩展点

- BeanPostProcessor 是对已经实例化的bean进行处理，BeanFactoryPostProcessor 是对未生成的bean，即bean的元数据进行处理，然后生成时会按这些元数据进行实例化。

##### 1.8.1. 使用 BeanPostProcessor 自定义 Bean

- 可以配置多个 `BeanPostProcessor` 实例，你可以通过设置 `order` 属性控制这些 `BeanPostProcessor` 实例的运行顺序。
- 当 `BeanPostProcessor` 被注册为容器的后处理器时，对于容器创建的每个 bean 实例，后处理器在容器初始化方法（如 `InitializingBean.afterPropertiesSet()` 或任何已声明的 `init` 方法）被调用之前和任何 bean 初始化回调之后都会从容器获得一个回调。

#### 1.8.2. 用 BeanFactoryPostProcessor 定制配置元数据

- 可以配置多个 `BeanFactoryPostProcessor` 实例，你可以通过设置 `order` 属性控制这些 `BeanFactoryPostProcessor` 实例的运行顺序。
- 当Bean工厂在 `ApplicationContext` 内声明时，会自动运行Bean工厂后处理器，以便对定义容器的配置元数据进行修改。

#### 1.8.3. 用 FactoryBean 自定义实例化逻辑

- 当你需要向容器索取一个实际的 `FactoryBean` 实例而不是它产生的Bean时，在调用 `ApplicationContext` 的 `getBean()` 方法时，在Bean的 `id` 前加上安培符号（`&`）。

#### 1.9. 基于注解的容器配置

- 注解注入是在XML注入之前进行的。因此，XML配置覆盖了通过这两种方法注入的属性的注解。

##### 1.9.1使用 @Autowired

- 可以将 `@Autowired` 注解应用于构造函数

- 可以将 `@Autowired` 注解应用于传统的setter方法

- 可以将 `@Autowired` 应用于具有任意名称和多个参数的方法

- 可以将 `@Autowired` 应用于字段，甚至将其与构造函数混合

- 可以指示Spring从 `ApplicationContext` 中提供所有特定类型的Bean，方法是将 `@Autowired` 注解添加到期望有该类型数组或类型化的（泛型）集合的字段或方法中

- 类型化的 `Map` 实例也可以被自动注入，只要预期的key类型是 `String`。

- 默认行为是将注解的方法和字段视为表示必须的依赖关系。你可以改变这种行为，就像下面的例子所展示的那样，通过将其标记为非必需（即通过将 `@Autowired` 中的 `required` 属性设置为 `false`），使框架能够跳过一个不可满足的注入点。

- 任何给定的Bean类中只有一个构造函数可以声明 `@Autowired`，并将 `required` 属性设置为 `true`，表示该构造函数在用作Spring Bean时要自动注入。

- 也可以使用 `@Nullable` 注解

  ```java
  public class SimpleMovieLister {
  
      @Autowired
      public void setMovieFinder(@Nullable MovieFinder movieFinder) {
          ...
      }
  }
  ```

- 可以通过Java 8的 `java.util.Optional` 来表达特定依赖的非必须性质

- 可以对那些众所周知的可解析依赖的接口使用 `@Autowired`。`BeanFactory`、`ApplicationContext`、`Environment`、`ResourceLoader`、`ApplicationEventPublisher` 和 `MessageSource`。

- `@Autowired`、`@Inject`、`@Value` 和 `@Resource` 注解是由Spring `BeanPostProcessor` 实现处理的。这意味着你不能在你自己的 `BeanPostProcessor` 或 `BeanFactoryPostProcessor` 类型（如果有的话）中应用这些注解。这些类型必须通过使用XML或Spring `@Bean` 方法明确地 "注入"。

##### 1.9.2. 用 @Primary 对基于注解的自动注入进行微调

- 当多个Bean是自动注入到一个单值（single value）依赖的候选者时，应该优先考虑一个特定的Bean。

##### 1.9.3. 用 Qualifiers 微调基于注解的自动注入

- 你可以将限定符的值与特定的参数联系起来，缩小类型匹配的范围，从而为每个参数选择一个特定的bean。
- 可以在单个构造函数参数或方法参数上指定 `@Qualifier` 注解
- Bean的名字被认为是默认的限定符值。
- 限定词不一定是唯一的。相反，它们构成过滤标准。
- 不推荐使用，使用JSR-250的 `@Resource` 注解。

##### 1.9.4. 使用泛型作为自动注入 Qualifier

##### 1.9.5. 使用 CustomAutowireConfigurer

##### 1.9.6. 用 @Resource 注入

- `@Resource` 需要一个 `name` 属性。默认情况下，Spring将该值解释为要注入的Bean名称。
- 如果没有明确指定名字，默认的名字来自于字段名或setter方法。如果是一个字段，它采用字段名。如果是setter方法，则采用Bean的属性名。

##### 1.9.7. 使用 @Value

- `@Value` 通常用于注入外部化properties。

- Spring Boot默认配置了一个 `PropertySourcesPlaceholderConfigurer` Bean，它将从 `application.properties` 和 `application.yml` 文件中获取属性。

- 可以提供一个默认值

  ```java
  @Value("${catalog.name:defaultCatalog}"
  ```

- 当 `@Value` 包含一个 SpEL 表达式 时，该值将在运行时被动态计算出来

  ```java
  @Value("#{systemProperties['user.catalog'] + 'Catalog' }"
  ```

##### 1.9.8. 使用 @PostConstruct 和 @PreDestroy

#### 1.10. Classpath扫描和管理的组件

##### 1.10.1. @Component 和进一步的 Stereotype 注解

- `@Repository`、 `@Service` 和 `@Controller` 是 `@Component` 的特殊化，用于更具体的使用情况（分别在持久层、服务层和表现层）。

##### 1.10.2. 使用元注解和组合注解

略简

##### 1.10.3. 自动检测类和注册Bean定义

```java
@Configuration
@ComponentScan(basePackages = "org.example")
public class AppConfig  {
    // ...
}
```

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xmlns:context="http://www.springframework.org/schema/context"
    xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/context
        https://www.springframework.org/schema/context/spring-context.xsd">

    <context:component-scan base-package="org.example"/>

</beans>
```

##### 1.10.4. 使用Filter来自定义扫描

- 可以通过应用自定义过滤器来修改和扩展这种行为。将它们作为 `@ComponentScan` 注解的 `includeFilters` 或 `excludeFilters` 属性（或作为XML配置中 `<context:component-scan>` 元素的 `<context:include-filter />` 或 `<context:exclud-filter />` 子元素）。

##### 1.10.5. 在组件中定义Bean元数据

- 可以用用于在 `@Configuration` 注解的类中定义Bean元数据的相同的 `@Bean` 注解来向容器贡献Bean定义元数据
- 对于 `@Value` 注解，表达式解析器被预设为在解析表达式文本名称。
- `@Component` 类没有用CGLIB来拦截方法和字段的调用。CGLIB代理是调用 `@Configuration` 类中 `@Bean` 方法中的方法或字段的方式，它创建了对协作对象的Bean元数据引用。

##### 1.10.6. 命名自动检测到的组件

- 默认的bean类名称生成器会返回未加大写的非限定类名称。

- ```java
  @ComponentScan(basePackages = "org.example", nameGenerator = MyNameGenerator.class)
  ```

##### 1.10.7. 为自动检测的组件提供一个Scope

```java
@Scope("prototype")
@Repository
public class MovieFinderImpl implements MovieFinder {
    // ...
}
```

##### 1.10.8. 用注解提供 Qualifier 元数据

略简

##### 1.10.9. 生成一个候选组件的索引

- 虽然classpath扫描非常快，但通过在编译时创建一个静态的候选列表，可以提高大型应用程序的启动性能。

- `spring-context-indexer` 工件会生成一个 `META-INF/spring.component` 文件，并包含在jar文件中。

- 当在`classpath`上发现 `META-INF/spring.component` 文件时，索引会自动启用。

```xml
<dependencies>
    <dependency>
        <groupId>org.springframework</groupId>
        <artifactId>spring-context-indexer</artifactId>
        <version>6.0.8-SNAPSHOT</version>
        <optional>true</optional>
    </dependency>
</dependencies>
```

#### 1.11. 使用JSR 330标准注解

##### 1.11.1. 用 @Inject 和 @Named 进行依赖注入

- 你可以使用 `@Jakarta.inject.Inject` 来代替 `@Autowired`
- 可以将你的注入点声明为一个 `Provider`，允许按需访问较短scope的Bean，或通过 `Provider.get()` 调用懒加载地访问其他Bean。
- 如果你想为应该被注入的依赖使用一个 qualifier 的名字，你应该使用 `@Named` 注解
- 可以与 `java.util.Optional` 或 `@Nullable` 一起使用。

##### 1.11.2. @Named 和 @ManagedBean：与 @Component 注解的标准对等物

- 可以使用 `@jakarta.inject.Named` 或 `jakarta.annotation.ManagedBean` 来代替 `@Component`

- 使用 `@Named` 而不指定组件的名称是很常见的

##### 1.11.3. JSR-330 标准注解的局限性

| Spring              | jakarta.inject.*      | jakarta.inject 限制 / 说明                                   |
| :------------------ | :-------------------- | :----------------------------------------------------------- |
| @Autowired          | @Inject               | `@Inject` 没有 'required' 属性。可以用 Java 8的 `Optional` 来代替。 |
| @Component          | @Named / @ManagedBean | JSR-330并没有提供一个可组合的模型，只是提供了一种识别命名组件的方法。 |
| @Scope("singleton") | @Singleton            | JSR-330的默认scope就像Spring的 `prototype`。然而，为了与Spring的一般默认值保持一致，在Spring容器中声明的JSR-330 Bean默认是一个 `singleton`。为了使用 `singleton` 以外的scope，你应该使用Spring的 `@Scope` 注解。`jakarta.inject` 也提供了一个 `jakarta.inject.Scope` 注解：不过，这个注解只用于创建自定义注解。 |
| @Qualifier          | @Qualifier / @Named   | `jakarta.inject.Qualifier` 只是一个用于构建自定义 qualifier 的元注解。具体的 `String` qualifier（像Spring的 `@Qualifier` 一样有一个值）可以通过 `jakarta.inject.Named` 来关联。 |
| @Value              | -                     | 没有对应的                                                   |
| @Lazy               | -                     | 没有对应的                                                   |
| ObjectFactory       | Provider              | `jakarta.inject.Provider` 是Spring的 `ObjectFactory` 的直接替代品，只是 `get()` 方法的名字比较短。它也可以与Spring的 `@Autowired` 结合使用，或者与非注解的构造器和setter方法结合使用。 |

#### 1.12. 基于Java的容器配置

##### 1.12.1 基本概念：@Bean 和 @Configuration

- `@Bean` 注解用来表示一个方法实例化、配置和初始化了一个新的对象，由Spring IoC容器管理。
- 用 `@Configuration` 来注解一个类，表明它的主要目的是作为Bean定义的来源。

##### 1.12.2 通过使用 AnnotationConfigApplicationContext 实例化Spring容器

###### 简单构造

- 可以在实例化 `AnnotationConfigApplicationContext` 时使用 `@Configuration` 类作为输入。
- 任何 `@Component` 或JSR-330注解的类都可以作为输入提供给 `AnnotationConfigApplicationContext` 构造函数

###### 通过使用 register(Class<?>…) 以编程方式构建容器

- 可以通过使用无参数构造函数来实例化 `AnnotationConfigApplicationContext`，然后通过 `register()` 方法来配置它。

###### 用 scan(String…) 启用组件扫描

- `AnnotationConfigApplicationContext` 暴露了 `scan(String…)` 方法，以实现同样的组件扫描功能

###### 用 AnnotationConfigWebApplicationContext 支持Web应用程序

```xml
<web-app>
    <!-- Configure ContextLoaderListener to use AnnotationConfigWebApplicationContext
        instead of the default XmlWebApplicationContext -->
    <context-param>
        <param-name>contextClass</param-name>
        <param-value>
            org.springframework.web.context.support.AnnotationConfigWebApplicationContext
        </param-value>
    </context-param>

    <!-- Configuration locations must consist of one or more comma- or space-delimited
        fully-qualified @Configuration classes. Fully-qualified packages may also be
        specified for component-scanning -->
    <context-param>
        <param-name>contextConfigLocation</param-name>
        <param-value>com.acme.AppConfig</param-value>
    </context-param>

    <!-- Bootstrap the root application context as usual using ContextLoaderListener -->
    <listener>
        <listener-class>org.springframework.web.context.ContextLoaderListener</listener-class>
    </listener>

    <!-- Declare a Spring MVC DispatcherServlet as usual -->
    <servlet>
        <servlet-name>dispatcher</servlet-name>
        <servlet-class>org.springframework.web.servlet.DispatcherServlet</servlet-class>
        <!-- Configure DispatcherServlet to use AnnotationConfigWebApplicationContext
            instead of the default XmlWebApplicationContext -->
        <init-param>
            <param-name>contextClass</param-name>
            <param-value>
                org.springframework.web.context.support.AnnotationConfigWebApplicationContext
            </param-value>
        </init-param>
        <!-- Again, config locations must consist of one or more comma- or space-delimited
            and fully-qualified @Configuration classes -->
        <init-param>
            <param-name>contextConfigLocation</param-name>
            <param-value>com.acme.web.MvcConfig</param-value>
        </init-param>
    </servlet>

    <!-- map all requests for /app/* to the dispatcher servlet -->
    <servlet-mapping>
        <servlet-name>dispatcher</servlet-name>
        <url-pattern>/app/*</url-pattern>
    </servlet-mapping>
</web-app>
```

##### 1.12.3. 使用 @Bean 注解

###### 声明一个 Bean

- 可以使用 default 方法来定义Bean
- 可以用一个接口（或基类）的返回类型来声明你的 `@Bean` 方法

###### Bean 依赖

###### 接收生命周期的回调

- 任何用 `@Bean` 注解定义的类都支持常规的生命周期回调，并且可以使用JSR-250的 `@PostConstruct` 和 `@PreDestroy` 注解。
- bean可以实现 `InitializingBean`、`DisposableBean` 或 `Lifecycle`，它们各自的方法就会被容器调用。
- 标准的 `*Aware` 接口集（如 BeanFactoryAware、BeanNameAware、MessageSourceAware、ApplicationContextAware 等）也被完全支持。
- `@Bean` 注解支持指定任意的初始化和销毁回调方法，就像Spring XML在 `bean` 元素上的 `init-method` 和 `destroy-method` 属性一样
- 默认情况下，用Java配置定义的具有 public 的 `close` 或 `shutdown` 方法的Bean会自动被列入销毁回调。也可通过 `@Bean(destroyMethod = "")` 来手动取消。

###### 指定 Bean 的 Scope

###### 使用 `@Scope` 注解

- 默认的scope是 `singleton`，但你可以用 `@Scope` 注解来覆盖它

###### @Scope 和 scoped-proxy

- 看不懂

###### 自定义Bean的命名

- 可以使用 ` @Bean({"dataSource", "subsystemA-dataSource", "subsystemB-dataSource"})` 来给bean命名 

###### Bean 别名

- 同上

###### Bean 描述（Description）

- `@Description("Provides a basic example of a bean")`

##### 1.12.4. 使用 @Configuration 注解

###### 注入bean间的依赖

```java
@Configuration
public class AppConfig {

    //会将beanTwo()生成的实例注入进来
    @Bean
    public BeanOne beanOne() {
        return new BeanOne(beanTwo());
    }

    @Bean
    public BeanTwo beanTwo() {
        return new BeanTwo;
    }
}
```

###### 查询方法注入

- 略简

###### 关于基于Java的配置如何在内部工作的进一步信息

- 略简

##### 1.12.5. 构建基于Java的配置

###### 使用 @Import 注解

- 略简

###### 有条件地包括 @Configuration 类或 @Bean 方法

- 一个常见的例子是使用 `@Profile` 注解来激活Bean

###### 将Java和XML配置相结合

- 以XML为中心使用 `@Configuration` 类

- `@Configuration` 以类为中心使用XML与 `@ImportResource`

#### 1.13. Environment 抽象

##### 1.13.1. Bean定义配置

###### 使用 @Profile

- `@Profile` 注解让你表明当一个或多个指定的配置文件处于活动状态时，一个组件就有资格注册

###### XML Bean 定义配置

```java
<beans xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xmlns:jdbc="http://www.springframework.org/schema/jdbc"
    xmlns:jee="http://www.springframework.org/schema/jee"
    xsi:schemaLocation="...">

    <!-- other bean definitions -->

    <beans profile="development">
        <jdbc:embedded-database id="dataSource">
            <jdbc:script location="classpath:com/bank/config/sql/schema.sql"/>
            <jdbc:script location="classpath:com/bank/config/sql/test-data.sql"/>
        </jdbc:embedded-database>
    </beans>

<!-- 如果 production 和 us-east profiles都处于活动状态，那么 dataSource Bean就会被暴露 -->            
    <beans profile="production">
        <beans profile="us-east">
            <jee:jndi-lookup id="dataSource" jndi-name="java:comp/env/jdbc/datasource"/>
        </beans>
    </beans>
</beans>
```

###### 激活一个 Profile

```properties
-Dspring.profiles.active="profile1,profile2"
```

###### 默认 Profile

```java
@Profile("default")
```

##### 1.13.2. PropertySource 抽象

对于一个普通的 `StandardServletEnvironment` 来说，完整的层次结构如下，最高优先级的条目在顶部。

- `ServletConfig` 参数（如果适用 - 例如，在 `DispatcherServlet` 上下文的情况下）。

- `ServletContext` 参数（web.xml的context-param条目）.

- JNDI环境变量（`java:comp/env/` 条目）。

- JVM系统属性（`-D` 命令行参数）。

- JVM系统环境（操作系统环境变量）.

##### 1.13.3. 使用 @PropertySource

```java
@Configuration
@PropertySource("classpath:/com/${my.placeholder:default/path}/app.properties")
public class AppConfig {

    @Autowired
    Environment env;

    @Bean
    public TestBean testBean() {
        TestBean testBean = new TestBean();
        testBean.setName(env.getProperty("testbean.name"));
        return testBean;
    }
}
```

##### 1.13.4. 声明中的占位符解析

- 简略

#### 1.14. 注册 LoadTimeWeaver

  - 略，后面有详细的

#### 1.15. ApplicationContext 的附加功能

##### 1.15.1. 使用 MessageSource 进行国际化

```java
public static void main(String[] args) {
    MessageSource resources = new ClassPathXmlApplicationContext("beans.xml");
    String message = resources.getMessage("message", null, "Default", Locale.ENGLISH);
    System.out.println(message);
}
```

##### 1.15.2. 标准和自定义事件

| 事件                         | 说明                                                         |
| :--------------------------- | :----------------------------------------------------------- |
| `ContextRefreshedEvent`      | 当 `ApplicationContext` 被初始化或刷新时发布（例如，通过使用 `ConfigurableApplicationContext` 接口上的 `refresh()` 方法）。这里，"初始化" 意味着所有的Bean都被加载，后处理器Bean被检测和激活，单例被预先实例化，并且 `ApplicationContext` 对象可以使用。只要上下文没有被关闭，就可以多次触发刷新，前提是所选的 `ApplicationContext` 实际上支持这种 "热" 刷新。例如， `XmlWebApplicationContext` 支持热刷新，但 `GenericApplicationContext` 不支持。 |
| `ContextStartedEvent`        | 当 `ApplicationContext` 通过使用 `ConfigurableApplicationContext` 接口上的 `start()` 方法启动时发布。在这里，"开始" 意味着所有的 `Lifecycle` Bean都收到一个显式的启动信号。通常，这个信号被用来在显式停止后重新启动Bean，但它也可能被用来启动那些没有被配置为自动启动的组件（例如，在初始化时还没有启动的组件）。 |
| `ContextStoppedEvent`        | 当 `ApplicationContext` 通过使用 `ConfigurableApplicationContext` 接口上的 `stop()` 方法而停止时发布。在这里，"停止" 意味着所有的 `Lifecycle` Bean收到一个明确的停止信号。停止的上下文可以通过调用 `start()` 重新启动。 |
| `ContextClosedEvent`         | 当 `ApplicationContext` 通过使用 `ConfigurableApplicationContext` 接口上的 `close()` 方法或通过 JVM shutdown hook 被关闭时发布。这里，"关闭" 意味着所有的单例Bean将被销毁。一旦上下文被关闭，它的生命就结束了，不能被刷新或重新启动。 |
| `RequestHandledEvent`        | 一个针对Web的事件，告诉所有Bean一个HTTP请求已经被处理。该事件在请求完成后被发布。这个事件只适用于使用Spring的 `DispatcherServlet` 的Web应用程序。 |
| `ServletRequestHandledEvent` | `RequestHandledEvent` 的一个子类，增加了 Servlet 特定的上下文信息。 |

- 可以创建和发布你自己的自定义事件。下面的例子展示了一个简单的类，它扩展了Spring的 `ApplicationEvent` 基类
- 通过创建一个实现 `ApplicationEventPublisherAware` 的类并将其注册为Spring Bean并调用`ApplicationEventPublisher` 的 `publishEvent()` 方法，发布一个自定义的 `ApplicationEvent`
- 接收自定义的 `ApplicationEvent`，你可以创建一个实现 `ApplicationListener` 的类并将其注册为Spring Bean。在默认情况下，事件监听器是同步接收事件的，这意味着 `publishEvent()` 方法会阻塞，直到所有的监听器都完成对事件的处理。
- 另一种事件发布策略，请参阅 Spring 的 `ApplicationEventMulticaster` 接口和 `SimpleApplicationEventMulticaster`

###### 基于注解的事件监听器

```java
@EventListener
@EventListener({ContextStartedEvent.class, ContextRefreshedEvent.class})
//只有在事件的 content 属性等于 my-event 时才会被调用。
@EventListener(condition = "#blEvent.content == 'my-event'")
```

`@EventListener` 中的 `spEl` 的上下文对象

| 名称       | 位置               | 说明                                                         | 示例                                                         |
| :--------- | :----------------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| 事件       | root 对象          | 实际的 `ApplicationEvent`。                                  | `#root.event` or `event`                                     |
| 参数数组   | root 对象          | 用于调用方法的参数（作为一个对象数组）。                     | `#root.args` 或 `args`; `args[0]` 用于访问第一个参数，等等。 |
| *参数名称* | evaluation context | 任何一个方法参数的名称。如果由于某种原因，这些名称无法使用（例如，因为在编译的字节码中没有debug信息），单个参数也可以使用 `#a<#arg>` 语法，其中 `<#arg>` 代表参数索引（从0开始）。 | `#blEvent` 或 `#a0`（你也可以使用 `#p0` 或 `#p<#arg>` 参数符号作为别名）。 |

```java
@EventListener
public ListUpdateEvent handleBlockedListEvent(BlockedListEvent event) {
    // notify appropriate parties via notificationAddress and
    // then publish a ListUpdateEvent...
    //如果你需要发布几个事件，你可以返回一个 Collection 或者一个事件数组来代替。
}
```

###### 异步监听器

```java
@EventListener
@Async
public void processBlockedListEvent(BlockedListEvent event) {
    // BlockedListEvent is processed in a separate thread
}
```

- 异步事件监听器方法不能通过返回一个值来发布后续的事件。如果你需要发布另一个事件作为处理的结果，请注入一个 `ApplicationEventPublisher` 来手动发布该事件

###### 监听顺序

- 如果你需要一个监听器在另一个之前被调用，你可以在方法声明中添加 `@Order` 注解

###### 一般性事件

- 用泛型来进一步定义你的事件的结构。考虑使用 `EntityCreatedEvent<T>`，其中 `T` 是被创建的实际实体的类型

- 如果多个事件为同一个泛型结构，则需要使用 `ResolvableTypeProvider` 接口

  ```java
  public class EntityCreatedEvent<T> extends ApplicationEvent implements ResolvableTypeProvider {
  
      public EntityCreatedEvent(T entity) {
          super(entity);
      }
  
      @Override
      public ResolvableType getResolvableType() {
          return ResolvableType.forClassWithGenerics(getClass(), ResolvableType.forInstance(getSource()));
      }
  }
  ```

##### 1.15.3. 方便地获取低级别的资源

- 略，后面有详细

##### 1.15.4. 应用程序启动跟踪

- 看不懂

##### 1.15.5. 为web应用程序提供方便的 ApplicationContext 实例化

- 看不懂

##### 1.15.6. 将 Spring ApplicationContext 部署为Jakarta EE RAR文件

- 看不懂，用不上

#### 1.16. BeanFactory API

##### 1.16.1. BeanFactory 还是 ApplicationContext?

### 2. 资源（Resources）

#### 2.1. 简介

#### 2.2. Resource接口

- 位于 `org.springframework.core.io.` 包中的Spring `Resource` 接口，旨在成为一个更有能力的接口，用于抽象访问低级资源。
- `Resource` 接口中最重要的一些方法是。
  - `getInputStream()`: 定位并打开资源，返回一个用于读取资源的 `InputStream`。我们期望每次调用都能返回一个新的 `InputStream`。关闭该流是调用者的责任。
  - `exists()`: 返回一个 `boolean` 值，表示该资源是否以物理形式实际存在。
  - `isOpen()`: 返回一个 `boolean`，表示该资源是否代表一个具有开放流的句柄。如果为 `true`，`InputStream` 不能被多次读取，必须只读一次，然后关闭以避免资源泄漏。对于所有通常的资源实现，除了 `InputStreamResource` 之外，返回 `false`。
  - `getDescription()`: 返回该资源的描述，用于处理该资源时的错误输出。这通常是全路径的文件名或资源的实际URL。
- `Resource` 接口的一些实现也实现了扩展的 `WritableResource` 接口，用于支持向其写入的资源。

#### 2.3. 内置的 Resource 实现

##### 2.4.1. UrlResource

- `UrlResource` 包装了一个 `java.net.URL`，可以用来访问任何通常可以用URL访问的对象，如文件、HTTPS目标、FTP目标等。

##### 2.3.2. ClassPathResource

- 从 classpath 获得的资源。它使用线程上下文的类加载器、一个给定的类加载器或一个给定的类来加载资源。

##### 2.3.3. FileSystemResource

- 用于 `java.io.File` 句柄 的 `Resource` 实现。它也支持 `java.nio.file.Path` 句柄，应用Spring标准的基于String的路径转换，但通过 `java.nio.file.Files` API执行所有操作。

##### 2.3.4. PathResource

- 用于 `java.nio.file.Path` 处理的 `Resource` 实现，通过 `Path` API执行所有操作和转换。它支持作为 `File` 和 `URL` 的解析，也实现了扩展的 `WritableResource` 接口。
- 是`FileSystemResource` 替代品。

##### 2.3.5. ServletContextResource

- 用于ServletContext资源的 `Resource` 实现，它解释了相对于Web应用根目录中的相对路径。
- 它总是支持流访问和URL访问，但只有当Web应用程序归档文件被扩展并且资源在文件系统上时才允许 `java.io.File` 访问。

##### 2.3.6. InputStreamResource

- `InputStreamResource` 是给定的 `InputStream` 的一个 `Resource` 实现。只有在没有特定的 `Resource` 实现的情况下才应该使用它。
- 在可能的情况下，最好选择 `ByteArrayResource` 或任何基于文件的 `Resource` 实现。

##### 2.3.7. ByteArrayResource

- 这是一个给定字节数组的 `Resource` 实现。它为给定的字节数组创建一个 `ByteArrayInputStream`。

#### 2.4. ResourceLoader 接口

- 所有的应用 `applicationContext` 都实现了 `ResourceLoader` 接口。

- `ClassPathXmlApplicationContext`，返回 `ClassPathResource`。

-  `FileSystemXmlApplicationContext` ，返回 `FileSystemResource`。

- 可以通过指定特殊的 `classpath:` 前缀来强制使用 `ClassPathResource`

  | 前缀       | 示例                             | 说明                                                         |
  | :--------- | :------------------------------- | :----------------------------------------------------------- |
  | classpath: | `classpath:com/myapp/config.xml` | 从classpath加载。                                            |
  | file:      | `file:///data/config.xml`        | 作为 `URL` 从文件系统加载。另请参见[`FileSystemResource` 注意事项](https://springdoc.cn/spring/core.html#resources-filesystemresource-caveats). |
  | https:     | `https://myserver/logo.png`      | 以 `URL` 形式加载。                                          |
  | (none)     | `/data/config.xml`               | 取决于底层的 `ApplicationContext'。                          |

#### 2.5. ResourcePatternResolver 接口

- `ResourcePatternResolver` 接口是对 `ResourceLoader` 接口的扩展，它定义了将位置模式（例如，Ant风格的路径模式）解析为 `Resource` 对象的策略。
- 这个接口定义了一个特殊的 `classpath*:` 资源前缀，用于所有来自类路径的匹配资源
- `PathMatchingResourcePatternResolver` 是一个独立的实现，可以在 `ApplicationContext` 之外使用，也可以被 `ResourceArrayPropertyEditor` 用于填充 `Resource[]` bean属性。`PathMatchingResourcePatternResolver` 能够将指定的资源位置路径解析为一个或多个匹配的 `Resource` 对象。
- `ApplicationContext` 实例实现了 `ResourcePatternResolver` 接口并委托给默认的 `PathMatchingResourcePatternResolver`。

#### 2.6.ResourceLoaderAware 接口

```java
public interface ResourceLoaderAware {

    void setResourceLoader(ResourceLoader resourceLoader);
}
```

- 应用识别 `ResourceLoaderAware` 并调用将自己作为参数  `setResourceLoader(ResourceLoader)`

#### 2.7. 作为依赖的 Resources

- 如果Bean本身要通过某种动态过程来确定和提供资源路径，那么Bean使用 `ResourceLoader` 或 `ResourcePatternResolver` 接口来加载资源可能是有意义的。

- 如果资源是静态的，完全不使用 `ResourceLoader` 接口（或 `ResourcePatternResolver` 接口）是有意义的，让Bean暴露它所需要的 `Resource` 属性，并期望它们被注入其中。

- ```java
  @Component
  public class MyBean {
  
      private final Resource template;
  	// 环境变量中有一个template.path的变量，对应值是资源路径
      // Spring将以字符串的形式检索模板路径的值，一个特殊的 PropertyEditor 将把字符串转换为 Resource 对象
      // 一个文件就用Resource对象，如果有多个文件则用数组对象
      public MyBean(@Value("${templates.path}") Resource[] templates) {
          this.template = template;
      }
  
      // ...
  }
  ```

####  2.8. Application Context 和资源路径

##### 2.8.1. 构建 Application Context

- 使用 `ClassPathXmlApplicationContext`，所以 bean 定义是从 classpath 中加载的。
- 使用 `FileSystemXmlApplicationContext`, 是从文件系统的一个位置（在这种情况下，相对于当前工作目录）加载的

##### 2.8.2. Application Context 构造器资源路径中的通配符

###### Ant 风格的 Pattern

###### 对可移植性的影响

- 强烈建议在你依赖它之前，在你的特定环境中对来自jar的资源的通配符解析进行彻底测试。

###### `classpath*:` 前缀

###### 与通配符有关的其他说明

##### 2.8.3. FileSystemResource 注意事项

- 当 `FileSystemApplicationContext` 为 `ResourceLoader` 时，情况会发生变化。`FileSystemApplicationContext` 强制所有附加的 `FileSystemResource` 实例将所有位置路径视为相对路径，无论它们是否以前导斜线开始。
- 如果需要真正的绝对文件系统路径，应避免使用 `FileSystemResource` 或 `FileSystemXmlApplicationContext` 的绝对路径，而是通过使用 `file:` URL 前缀强制使用 `UrlResource`。

### 3. 验证、数据绑定和类型转换

#### 3.1. 使用 Spring 的 Validator 接口进行验证

- 实现 `org.springframework.validation.Validator` 接口的以下两个方法为 `Person` 类提供验证行为。
  - `supports(Class)`: 这个 `Validator` 可以验证提供的 `Class` 的实例吗？
  - `validate(Object, org.springframework.validation.Errors)`: 验证给定的对象，如果出现验证错误，则用给定的 `Errors` 对象登记这些错误。
- Spring框架也提供的 `ValidationUtils` 帮助类时

#### 3.2. 将code解析为错误信息

- 默认情况下，使用 `DefaultMessageCodesResolver`，它（例如）不仅用你给的代码注册了一条消息，而且还注册了包括你传递给拒绝方法的字段名的消息。

#### 3.3. Bean 操作和 `BeanWrapper`

- `org.springframework.beans` 包遵守 JavaBeans 标准。
- `BeanWrapper` 提供了设置和获取属性值（单独或批量）
- 获取属性描述符以及查询属性以确定它们是否可读或可写的功能
- `BeanWrapper` 还提供了对嵌套属性的支持

##### 3.3.1. 设置和获取基本属性和嵌套属性

- 设置和获取属性是通过 `BeanWrapper` 的 `setPropertyValue` 和 `getPropertyValue` 重载方法变体完成的。

  | 表达式                 | 说明                                                         |
  | ---------------------- | ------------------------------------------------------------ |
  | `name`                 | 表示与 `getName()` 或 `isName()` 和 `setName(..)` 方法相对应的属性 `name`。 |
  | `account.name`         | 表示与（例如）`getAccount().setName()` 或 `getAccount().getName()` 方法相对应的属性 `account` 的嵌套属性 `name`。 |
  | `account[2]`           | 表示索引属性 `account` 的第三个元素。索引属性可以是 `array`、`list` 或其他自然有序的集合类型。 |
  | `account[COMPANYNAME]` | 表示由 `account` `Map` 属性的 `COMPANYNAME` key 索引的 map 条目的值。 |

##### 3.3.2. 内置的 PropertyEditor 实现

- Spring使用 `PropertyEditor` 的概念来实现 `Object` 和 `String` 之间的转换。

  | 类                        | 说明                                                         |
  | ------------------------- | ------------------------------------------------------------ |
  | `ByteArrayPropertyEditor` | 字节数组的编辑器。将字符串转换为其相应的字节表示。默认由 `BeanWrapperImpl` 注册。 |
  | `ClassEditor`             | 将代表类的字符串解析为实际的类，反之亦然。当没有找到一个类时，会抛出一个 `IllegalArgumentException`。默认情况下，通过 `BeanWrapperImpl` 注册。 |
  | `CustomBooleanEditor`     | 用于 `Boolean` 属性的可定制的属性编辑器。默认情况下，由 `BeanWrapperImpl` 注册，但可以通过注册它的一个自定义实例作为自定义编辑器来重写。 |
  | `CustomCollectionEditor`  | 集合的属性编辑器，将任何源 `Collection` 转换为一个给定的目标 `Collection`  类型。 |
  | `CustomDateEditor`        | `java.util.Date` 的可定制属性编辑器，支持自定义 `DateFormat`。默认情况下没有注册。必须根据需要由用户注册适当的格式（format）。 |
  | `CustomNumberEditor`      | 可定制的属性编辑器，用于任何 `Number` 子类，如 `Integer`、`Long`、`Float` 或 `Double`。默认情况下，由 `BeanWrapperImpl` 注册，但可以通过注册它的一个自定义实例作为自定义编辑器来重写。 |
  | `FileEditor`              | 将字符串解析为 `java.io.File` 对象。默认情况下，由 `BeanWrapperImpl` 注册。 |
  | `InputStreamEditor`       | 单向属性编辑器，可以接受一个字符串并产生（通过中间的 `ResourceEditor` 和 `Resource`）一个 `InputStream`，这样 `InputStream` 属性可以直接设置为字符串。注意，默认用法不会为你关闭 `InputStream`。默认情况下，由 `BeanWrapperImpl` 注册。 |
  | `LocaleEditor`            | 可以将字符串解析为 `Locale` 对象，反之亦然（字符串格式为 `[language]_[country]_[variant]`，与 `Locale` 的 `toString()` 方法相同）。也接受空格作为分隔符，作为下划线的替代。默认情况下，由 `BeanWrapperImpl` 注册。 |
  | `PatternEditor`           | 可以将字符串解析为 `java.util.regex.Pattern` 对象，反之亦然。 |
  | `PropertiesEditor`        | 可以将字符串（格式为 `java.util.Properties` 类的javadoc中定义的格式）转换为 `Properties` 对象。默认情况下，由 `BeanWrapperImpl` 注册。 |
  | `StringTrimmerEditor`     | trim 字符串的属性编辑器。可选择允许将空字符串转换为 `null` 值。默认情况下没有注册 - 必须由用户注册。 |
  | `URLEditor`               | 可以将一个 URL 的字符串表示解析为一个实际的 `URL` 对象。默认情况下，由 `BeanWrapperImpl` 注册。 |

- 如果 `PropertyEditor` 类与它们所处理的类在同一个包中，并且与该类的名称相同，并附加了 `Editor`，那么标准的JavaBeans基础设施就会自动发现这些类。也可以在这里使用标准的 `BeanInfo` JavaBeans机制

###### 注册额外的自定义 `PropertyEditor` 实现

- 使用 `ConfigurableBeanFactory` 接口的 `registerCustomEditor()` 方法，不推荐。

- 使用 `CustomEditorConfigurer` 注册。

  ```xml
  <bean class="org.springframework.beans.factory.config.CustomEditorConfigurer">
      <property name="customEditors">
          <map>
              <entry key="example.ExoticType" value="example.ExoticTypeEditor"/>
          </map>
      </property>
  </bean>
  ```

###### 使用 `PropertyEditorRegistrar`

```java
public final class CustomPropertyEditorRegistrar implements PropertyEditorRegistrar {

    public void registerCustomEditors(PropertyEditorRegistry registry) {

        // it is expected that new PropertyEditor instances are created
        registry.registerCustomEditor(ExoticType.class, new ExoticTypeEditor());

        // you could register as many custom property editors as are required here...
    }
}
```

#### 3.4. Spring 类型转换

##### 3.4.1. 转换器（Converter） SPI

```java
package org.springframework.core.convert.converter;

public interface Converter<S, T> {

    T convert(S source);
}
```

- `core.convert.support` 包中提供了几个converter的实现，作为一种便利。

##### 3.4.2. 使用 `ConverterFactory`

- spirng实例化后可以对controller传入的类型自动转换，例如传入string转为enum。

##### 3.4.3. 使用 `GenericConverter`

- 不常用

```java
package org.springframework.core.convert.converter;

public interface GenericConverter {
	//支持的源类型 → 目标类型对
    public Set<ConvertiblePair> getConvertibleTypes();
	//转换逻辑
    Object convert(Object source, TypeDescriptor sourceType, TypeDescriptor targetType);
}
```

###### 使用 `ConditionalGenericConverter`

- matches方法检查通过时才转换

```java
public interface ConditionalConverter {

    boolean matches(TypeDescriptor sourceType, TypeDescriptor targetType);
}

public interface ConditionalGenericConverter extends GenericConverter, ConditionalConverter {
}
```

##### 3.4.4. `ConversionService` API

- `core.convert.support` 包中提供了一个强大的 `ConversionService` 实现 GenericConversionService。

```java
package org.springframework.core.convert;

public interface ConversionService {

    boolean canConvert(Class<?> sourceType, Class<?> targetType);

    <T> T convert(Object source, Class<T> targetType);

    boolean canConvert(TypeDescriptor sourceType, TypeDescriptor targetType);

    Object convert(Object source, TypeDescriptor sourceType, TypeDescriptor targetType);
}
```

##### 3.4.5. 配置 `ConversionService`

- 如果没有向Spring注册 `ConversionService`，就会使用基于 `PropertyEditor` 的原始系统。

```xml
<bean id="conversionService"
        class="org.springframework.context.support.ConversionServiceFactoryBean">
    <property name="converters">
        <set>
            <bean class="example.MyCustomConverter"/>
        </set>
    </property>
</bean>
```

##### 3.4.6. 以编程方式使用 `ConversionService`

```java
@Service
public class MyService {

    public MyService(ConversionService conversionService) {
        this.conversionService = conversionService;
    }

    public void doIt() {
        this.conversionService.convert(...)
    }
}
```



#### 3.5. Spring 字段格式化

##### 3.5.1. `Formatter` SPI

```java
package org.springframework.format;

public interface Formatter<T> extends Printer<T>, Parser<T> {
}
```

```java
public interface Printer<T> {

    String print(T fieldValue, Locale locale);
}
```

```java
public interface Parser<T> {

    T parse(String clientValue, Locale locale) throws ParseException;
}
```

##### 3.5.2. 注解驱动的格式化

```java
package org.springframework.format;

public interface AnnotationFormatterFactory<A extends Annotation> {

    Set<Class<?>> getFieldTypes();

    Printer<?> getPrinter(A annotation, Class<?> fieldType);

    Parser<?> getParser(A annotation, Class<?> fieldType);
}
```





```java
public final class NumberFormatAnnotationFormatterFactory
        implements AnnotationFormatterFactory<NumberFormat> {

    private static final Set<Class<?>> FIELD_TYPES = Set.of(Short.class,
            Integer.class, Long.class, Float.class, Double.class,
            BigDecimal.class, BigInteger.class);

    public Set<Class<?>> getFieldTypes() {
        return FIELD_TYPES;
    }

    public Printer<Number> getPrinter(NumberFormat annotation, Class<?> fieldType) {
        return configureFormatterFrom(annotation, fieldType);
    }

    public Parser<Number> getParser(NumberFormat annotation, Class<?> fieldType) {
        return configureFormatterFrom(annotation, fieldType);
    }

    private Formatter<Number> configureFormatterFrom(NumberFormat annotation, Class<?> fieldType) {
        if (!annotation.pattern().isEmpty()) {
            return new NumberStyleFormatter(annotation.pattern());
        }
        // else
        return switch(annotation.style()) {
            case Style.PERCENT -> new PercentStyleFormatter();
            case Style.CURRENCY -> new CurrencyStyleFormatter();
            default -> new NumberStyleFormatter();
        };
    }
}
```





```java
public class MyModel {

    @NumberFormat(style=Style.CURRENCY)
    private BigDecimal decimal;
}
```



##### 格式化注解API

```java
public class MyModel {

    @DateTimeFormat(iso=ISO.DATE)
    private Date date;
}
```

##### 3.5.3. `FormatterRegistry` SPI

-  `FormattingConversionService` 是 `FormatterRegistry` 的一个实现，适用于大多数环境。

```java
package org.springframework.format;

public interface FormatterRegistry extends ConverterRegistry {

    void addPrinter(Printer<?> printer);

    void addParser(Parser<?> parser);

    void addFormatter(Formatter<?> formatter);

    void addFormatterForFieldType(Class<?> fieldType, Formatter<?> formatter);

    void addFormatterForFieldType(Class<?> fieldType, Printer<?> printer, Parser<?> parser);

    void addFormatterForFieldAnnotation(AnnotationFormatterFactory<? extends Annotation> annotationFormatterFactory);
}
```

##### 3.5.4. `FormatterRegistrar` SPI

```java
package org.springframework.format;

public interface FormatterRegistrar {

    void registerFormatters(FormatterRegistry registry);
}
```

- 用于通过 `FormatterRegistry` 来注册formatter和converter

#### 3.6. 配置全局的 Date 和 Time 的格式

- 默认情况下，没有用 `@DateTimeFormat` 注解的date和time字段通过使用 `DateFormat.SHORT` 样式从字符串转换
- `org.springframework.format.datetime.standard.DateTimeFormatterRegistrar`
- `org.springframework.format.datetime.DateFormatterRegistrar`
- 例如配置注册了一个全局 `YYYMMDD` 格式

```java
@Configuration
public class AppConfig {

    @Bean
    public FormattingConversionService conversionService() {

        // Use the DefaultFormattingConversionService but do not register defaults
        DefaultFormattingConversionService conversionService =
            new DefaultFormattingConversionService(false);

        // Ensure @NumberFormat is still supported
        conversionService.addFormatterForFieldAnnotation(
            new NumberFormatAnnotationFormatterFactory());

        // Register JSR-310 date conversion with a specific global format
        DateTimeFormatterRegistrar dateTimeRegistrar = new DateTimeFormatterRegistrar();
        dateTimeRegistrar.setDateFormatter(DateTimeFormatter.ofPattern("yyyyMMdd"));
        dateTimeRegistrar.registerFormatters(conversionService);

        // Register date conversion with a specific global format
        DateFormatterRegistrar dateRegistrar = new DateFormatterRegistrar();
        dateRegistrar.setFormatter(new DateFormatter("yyyyMMdd"));
        dateRegistrar.registerFormatters(conversionService);

        return conversionService;
    }
}
```

#### 3.7. Java Bean 校验

##### 3.7.1. Bean 校验（Validation）的概述

##### 3.7.2. 配置一个Bean Validation Provider

```java
@Configuration
public class AppConfig {

    @Bean
    public LocalValidatorFactoryBean validator() {
        return new LocalValidatorFactoryBean();
    }
}
```



##### 注入一个 Validator

```java
@Service
public class MyService {

    @Autowired
    private Validator validator;
}
```



##### 配置自定义约束

- 每个bean验证约束由两部分组成。	
  - 一个 `@Constraint` 注解，声明了约束及其可配置的属性。
  - `jakarta.validation.ConstraintValidator` 接口的一个实现，实现约束的行为。

```java
@Target({ElementType.METHOD, ElementType.FIELD})
@Retention(RetentionPolicy.RUNTIME)
@Constraint(validatedBy=MyConstraintValidator.class)
public @interface MyConstraint {
}
```

```java
public class MyConstraintValidator implements ConstraintValidator {

    @Autowired;
    private Foo aDependency;

    // ...
}
```

##### Spring驱动的方法验证

- 可以通过 `MethodValidationPostProcessor` Bean定义将Bean Validation 1.1支持的方法验证功能（作为自定义扩展，Hibernate Validator 4.3也支持）集成到Spring context中

```java
@Configuration
public class AppConfig {

    @Bean
    public MethodValidationPostProcessor validationPostProcessor() {
        return new MethodValidationPostProcessor();
    }
}
```

##### 其他配置选项

#### 3.7.3. 配置 `DataBinder`

### 4. Spring 表达式语言（SpEL）

#### 4.1. 评估（Evaluation）

- `ExpressionParser` 接口负责解析一个表达式字符串。
- `Expression` 接口负责评估先前定义的表达式字符串。
- 在调用 `parser.parseExpression` 和 `exp.getValue` 时，可以分别抛出两个异常，即 `ParseException` 和 `EvaluationException`。

##### 4.1.1. 理解 `EvaluationContext`

- `SimpleEvaluationContext`: 暴露了SpEL语言的基本特征和配置选项的一个子集，适用于不需要SpEL语言语法的全部范围，并且应该被有意义地限制的表达类别。例如，包括但不限于数据绑定表达式和基于属性的过滤器。`SimpleEvaluationContext` 被设计为只支持SpEL语言语法的一个子集。它排除了Java类型引用、构造函数和Bean引用。默认情况下， `create()` 静态工厂方法只允许对属性进行读取访问。你也可以获得一个 builder 来配置所需的确切支持级别。
- `StandardEvaluationContext`: 暴露了全套的SpEL语言功能和配置选项。你可以用它来指定一个默认的根对象，并配置每个可用的评估相关策略。

###### 类型转换

- SpEL使用Spring core中提供的转换服务（`org.springframework.core.convert.ConversionService`）。这个转换服务为常见的转换提供了许多内置的转换器，但也是完全可扩展的。

##### 4.1.2. 解析器（Parser ）配置

- 可以通过使用解析器配置对象（`org.springframework.expression.spel.SpelParserConfiguration`）来配置SpEL表达式解析器。

```java
// Turn on:
// - auto null reference initialization
// - auto collection growing
SpelParserConfiguration config = new SpelParserConfiguration(true, true);
```

##### 4.1.3. SpEL 编译

- `OFF` (默认)：编译器被关闭。
- `IMMEDIATE`: 在即时模式下，表达式被尽快编译。这通常是在第一次解释的评估之后。如果编译的表达式失败（通常是由于类型改变，如前所述），表达式评估的调用者会收到一个异常。
- `MIXED`: 在混合模式下，表达式随着时间的推移在解释模式和编译模式之间默默地切换。在经过一定数量的解释运行后，它们会切换到编译形式，如果编译形式出了问题（比如类型改变，如前所述），表达式会自动再次切换回解释形式。稍后的某个时候，它可能会生成另一个编译形式并切换到它。基本上，用户在 `IMMEDIATE` 模式下得到的异常反而被内部处理。

```java
SpelParserConfiguration config = new SpelParserConfiguration(SpelCompilerMode.IMMEDIATE,
        this.getClass().getClassLoader());

SpelExpressionParser parser = new SpelExpressionParser(config);

Expression expr = parser.parseExpression("payload");

MyMessage message = new MyMessage();

Object payload = expr.getValue(message);
```

或

```properties
spring.expression.compiler.mode = off
```

#### 4.2. Bean定义中的表达式

- 可以使用SpEL表达式与基于XML或基于注解的配置元数据来定义 `BeanDefinition` 实例。在这两种情况下，定义表达式的语法都是 `#{ <expression string> }` 的形式。

##### 4.2.1. XML 配置

```xml
<bean id="numberGuess" class="org.spring.samples.NumberGuess">
    <property name="randomNumber" value="#{ T(java.lang.Math).random() * 100.0 }"/>

    <!-- other properties -->
</bean>
<bean id="shapeGuess" class="org.spring.samples.ShapeGuess">
    <property name="initialShapeSeed" value="#{ numberGuess.randomNumber }"/>

    <!-- other properties -->
</bean>
```

```xml
<bean id="taxCalculator" class="org.spring.samples.TaxCalculator">
    <property name="defaultLocale" value="#{ systemProperties['user.region'] }"/>

    <!-- other properties -->
</bean>
```

##### 4.2.2. 注解配置

```java
public class FieldValueTestBean {

    @Value("#{ systemProperties['user.region'] }")
    private String defaultLocale;

    public void setDefaultLocale(String defaultLocale) {
        this.defaultLocale = defaultLocale;
    }

    public String getDefaultLocale() {
        return this.defaultLocale;
    }
}
```

```java
public class SimpleMovieLister {

    private MovieFinder movieFinder;
    private String defaultLocale;

    @Autowired
    public void configure(MovieFinder movieFinder,
            @Value("#{ systemProperties['user.region'] }") String defaultLocale) {
        this.movieFinder = movieFinder;
        this.defaultLocale = defaultLocale;
    }

    // ...
}
```

#### 4.3. 语言参考

##### 4.3.1. 字面值上的表达

- string：字符串可以用单引号（`'`）或双引号（`"`）来限定。要在一个用单引号括起来的字符串字头中包含一个单引号，请使用两个相邻的单引号字符。同样，要在一个用双引号括起来的字符串字面中包含一个双引号，请使用两个相邻的双引号字符。
- 数值: integer (`int` 或 `long`), 十六进制 (`int` 或 `long`), real (`float` 或 `double`)：数字支持使用负号、指数符号和小数点。默认情况下，实数是通过使用 `Double.parseDouble()` 来解析的。
- boolean 值: `true` 或 `false`
- null

##### 4.3.2. Properties、Array、List、Map 和索引

```java
// evaluates to 1856
int year = (Integer) parser.parseExpression("birthdate.year + 1900").getValue(context);

String city = (String) parser.parseExpression("placeOfBirth.city").getValue(context);
```

```java
ExpressionParser parser = new SpelExpressionParser();
EvaluationContext context = SimpleEvaluationContext.forReadOnlyDataBinding().build();

// Inventions Array

// evaluates to "Induction motor"
String invention = parser.parseExpression("inventions[3]").getValue(
        context, tesla, String.class);

// Members List

// evaluates to "Nikola Tesla"
String name = parser.parseExpression("members[0].name").getValue(
        context, ieee, String.class);

// List and Array navigation
// evaluates to "Wireless communication"
String invention = parser.parseExpression("members[0].inventions[6]").getValue(
        context, ieee, String.class);
```

```java
// Officer's Dictionary

Inventor pupin = parser.parseExpression("officers['president']").getValue(
        societyContext, Inventor.class);

// evaluates to "Idvor"
String city = parser.parseExpression("officers['president'].placeOfBirth.city").getValue(
        societyContext, String.class);

// setting values
parser.parseExpression("officers['advisors'][0].placeOfBirth.country").setValue(
        societyContext, "Croatia");
```

##### 4.3.3. 内联列表

```java
// evaluates to a Java list containing the four numbers
List numbers = (List) parser.parseExpression("{1,2,3,4}").getValue(context);

List listOfLists = (List) parser.parseExpression("{{'a','b'},{'x','y'}}").getValue(context);
```



##### 4.3.4. 内联Map

- `{:}` 本身意味着一个空map。

```java
// evaluates to a Java map containing the two entries
Map inventorInfo = (Map) parser.parseExpression("{name:'Nikola',dob:'10-July-1856'}").getValue(context);

Map mapOfMaps = (Map) parser.parseExpression("{name:{first:'Nikola',last:'Tesla'},dob:{day:10,month:'July',year:1856}}").getValue(context);
```

##### 4.3.5. Array 构造

```java
int[] numbers1 = (int[]) parser.parseExpression("new int[4]").getValue(context);

// Array with initializer
int[] numbers2 = (int[]) parser.parseExpression("new int[]{1,2,3}").getValue(context);

// Multi dimensional array
int[][] numbers3 = (int[][]) parser.parseExpression("new int[4][5]").getValue(context);
```

##### 4.3.6. 方法

```java
// string literal, evaluates to "bc"
String bc = parser.parseExpression("'abc'.substring(1, 3)").getValue(String.class);

// evaluates to true
boolean isMember = parser.parseExpression("isMember('Mihajlo Pupin')").getValue(
        societyContext, Boolean.class);
```



##### 4.3.7. 操作

###### 关系操作符

- 任何其他的值总是大于 `null`（ `X > null` 总是 `true`）
- 对原始类型要小心，因为它们会立即被包装在它们的封装类型上。例如，`1 instanceof T(int)` 的值为 `false`，而 `1 instanceof T(Integer)` 的值为 `true`.

```java
// evaluates to true
boolean trueValue = parser.parseExpression("2 == 2").getValue(Boolean.class);

// evaluates to false
boolean falseValue = parser.parseExpression("2 < -5.0").getValue(Boolean.class);

// evaluates to true
boolean trueValue = parser.parseExpression("'black' < 'block'").getValue(Boolean.class);

// uses CustomValue:::compareTo
boolean trueValue = parser.parseExpression("new CustomValue(1) < new CustomValue(2)").getValue(Boolean.class);

// evaluates to false
boolean falseValue = parser.parseExpression(
        "'xyz' instanceof T(Integer)").getValue(Boolean.class);

// evaluates to true
boolean trueValue = parser.parseExpression(
        "'5.00' matches '^-?\\d+(\\.\\d{2})?$'").getValue(Boolean.class);

// evaluates to false
boolean falseValue = parser.parseExpression(
        "'5.0067' matches '^-?\\d+(\\.\\d{2})?$'").getValue(Boolean.class);
```

###### 逻辑运算符

```java
// -- AND --

// evaluates to false
boolean falseValue = parser.parseExpression("true and false").getValue(Boolean.class);

// evaluates to true
String expression = "isMember('Nikola Tesla') and isMember('Mihajlo Pupin')";
boolean trueValue = parser.parseExpression(expression).getValue(societyContext, Boolean.class);

// -- OR --

// evaluates to true
boolean trueValue = parser.parseExpression("true or false").getValue(Boolean.class);

// evaluates to true
String expression = "isMember('Nikola Tesla') or isMember('Albert Einstein')";
boolean trueValue = parser.parseExpression(expression).getValue(societyContext, Boolean.class);

// -- NOT --

// evaluates to false
boolean falseValue = parser.parseExpression("!true").getValue(Boolean.class);

// -- AND and NOT --
String expression = "isMember('Nikola Tesla') and !isMember('Mihajlo Pupin')";
boolean falseValue = parser.parseExpression(expression).getValue(societyContext, Boolean.class);
```

###### 数学操作符

```java
// Addition
int two = parser.parseExpression("1 + 1").getValue(Integer.class);  // 2

String testString = parser.parseExpression(
        "'test' + ' ' + 'string'").getValue(String.class);  // 'test string'

// Subtraction
int four = parser.parseExpression("1 - -3").getValue(Integer.class);  // 4

double d = parser.parseExpression("1000.00 - 1e4").getValue(Double.class);  // -9000

// Multiplication
int six = parser.parseExpression("-2 * -3").getValue(Integer.class);  // 6

double twentyFour = parser.parseExpression("2.0 * 3e0 * 4").getValue(Double.class);  // 24.0

// Division
int minusTwo = parser.parseExpression("6 / -3").getValue(Integer.class);  // -2

double one = parser.parseExpression("8.0 / 4e0 / 2").getValue(Double.class);  // 1.0

// Modulus
int three = parser.parseExpression("7 % 4").getValue(Integer.class);  // 3

int one = parser.parseExpression("8 / 5 % 2").getValue(Integer.class);  // 1

// Operator precedence
int minusTwentyOne = parser.parseExpression("1+2-3*8").getValue(Integer.class);  // -21
```

###### 赋值运算符

- 可以使用赋值运算符（`=`），但是这通常是在调用 `setValue` 时进行。

```java
Inventor inventor = new Inventor();
EvaluationContext context = SimpleEvaluationContext.forReadWriteDataBinding().build();

parser.parseExpression("name").setValue(context, inventor, "Aleksandar Seovic");

// alternatively
String aleks = parser.parseExpression(
        "name = 'Aleksandar Seovic'").getValue(context, inventor, String.class);
```



##### 4.3.8. 类型

```java
Class dateClass = parser.parseExpression("T(java.util.Date)").getValue(Class.class);

Class stringClass = parser.parseExpression("T(String)").getValue(Class.class);

boolean trueValue = parser.parseExpression(
        "T(java.math.RoundingMode).CEILING < T(java.math.RoundingMode).FLOOR")
        .getValue(Boolean.class);
```



##### 4.3.9. 构造器

```java
Inventor einstein = p.parseExpression(
        "new org.spring.samples.spel.inventor.Inventor('Albert Einstein', 'German')")
        .getValue(Inventor.class);

// create new Inventor instance within the add() method of List
p.parseExpression(
        "Members.add(new org.spring.samples.spel.inventor.Inventor(
            'Albert Einstein', 'German'))").getValue(societyContext);
```



##### 4.3.10. 变量

```java
Inventor tesla = new Inventor("Nikola Tesla", "Serbian");

EvaluationContext context = SimpleEvaluationContext.forReadWriteDataBinding().build();
context.setVariable("newName", "Mike Tesla");

parser.parseExpression("name = #newName").getValue(context, tesla);
System.out.println(tesla.getName())  // "Mike Tesla"
```

###### `#this` 和 `#root` 变量

```java
// create an array of integers
List<Integer> primes = new ArrayList<>();
primes.addAll(Arrays.asList(2,3,5,7,11,13,17));

// create parser and set variable 'primes' as the array of integers
ExpressionParser parser = new SpelExpressionParser();
EvaluationContext context = SimpleEvaluationContext.forReadOnlyDataAccess();
context.setVariable("primes", primes);

// all prime numbers > 10 from the list (using selection ?{...})
// evaluates to [11, 13, 17]
List<Integer> primesGreaterThanTen = (List<Integer>) parser.parseExpression(
        "#primes.?[#this>10]").getValue(context);
```



##### 4.3.11. 函数

```java
ExpressionParser parser = new SpelExpressionParser();

EvaluationContext context = SimpleEvaluationContext.forReadOnlyDataBinding().build();
context.setVariable("reverseString",
        StringUtils.class.getDeclaredMethod("reverseString", String.class));

String helloWorldReversed = parser.parseExpression(
        "#reverseString('hello')").getValue(context, String.class);
```



##### 4.3.12. Bean 引用

```java
ExpressionParser parser = new SpelExpressionParser();
StandardEvaluationContext context = new StandardEvaluationContext();
context.setBeanResolver(new MyBeanResolver());

// This will end up calling resolve(context,"something") on MyBeanResolver during evaluation
Object bean = parser.parseExpression("@something").getValue(context);

// This will end up calling resolve(context,"&foo") on MyBeanResolver during evaluation
//访问 factory Bean 本身，你应该在Bean的名字前加上一个 & 符号。
Object bean = parser.parseExpression("&foo").getValue(context);
```



##### 4.3.13. 三元运算符（If-Then-Else）

```java
parser.parseExpression("name").setValue(societyContext, "IEEE");
societyContext.setVariable("queryName", "Nikola Tesla");

expression = "isMember(#queryName)? #queryName + ' is a member of the ' " +
        "+ Name + ' Society' : #queryName + ' is not a member of the ' + Name + ' Society'";

String queryResultString = parser.parseExpression(expression)
        .getValue(societyContext, String.class);
// queryResultString = "Nikola Tesla is a member of the IEEE Society"
```



##### 4.3.14. 埃尔维斯（Elvis）运算符

```java
ExpressionParser parser = new SpelExpressionParser();
EvaluationContext context = SimpleEvaluationContext.forReadOnlyDataBinding().build();

Inventor tesla = new Inventor("Nikola Tesla", "Serbian");
String name = parser.parseExpression("name?:'Elvis Presley'").getValue(context, tesla, String.class);
System.out.println(name);  // Nikola Tesla

tesla.setName(null);
name = parser.parseExpression("name?:'Elvis Presley'").getValue(context, tesla, String.class);
System.out.println(name);  // Elvis Presley
```

```java
@Value("#{systemProperties['pop3.port'] ?: 25}")
```



##### 4.3.15. 安全的导航操作

```java
ExpressionParser parser = new SpelExpressionParser();
EvaluationContext context = SimpleEvaluationContext.forReadOnlyDataBinding().build();

Inventor tesla = new Inventor("Nikola Tesla", "Serbian");
tesla.setPlaceOfBirth(new PlaceOfBirth("Smiljan"));

String city = parser.parseExpression("placeOfBirth?.city").getValue(context, tesla, String.class);
System.out.println(city);  // Smiljan

tesla.setPlaceOfBirth(null);
city = parser.parseExpression("placeOfBirth?.city").getValue(context, tesla, String.class);
System.out.println(city);  // null - does not throw NullPointerException!!!
```



##### 4.3.16. Collection Selection（选择）

- 返回所有选择的元素外，你还可以只检索第一个或最后一个元素。要获得与选择匹配的第一个元素，语法是 `.^[selectionExpression]`。要获得最后一个匹配的选择，其语法是 `.$[selectionExpression]`。

```java
List<Inventor> list = (List<Inventor>) parser.parseExpression(
        "members.?[nationality == 'Serbian']").getValue(societyContext);
```



##### 4.3.17. Collection 投影

- 从一个 `List<Object>` 转为一个 `List<String>`

```java
// returns ['Smiljan', 'Idvor' ]
List placesOfBirth = (List)parser.parseExpression("members.![placeOfBirth.city]");
```



##### 4.3.18. 表达式模板化

### 5. 用Spring进行面向切面的编程

#### 5.1. AOP 概念

- Aspect（切面）: 一个跨越多个类的关注点的模块化。事务管理是企业级Java应用中横切关注点的一个很好的例子。在Spring AOP中，切面是通过使用常规类（基于 [schema 的方法](https://springdoc.cn/spring/core.html#aop-schema)）或使用 `@Aspect` 注解的常规类（[@AspectJ](https://springdoc.cn/spring/core.html#aop-ataspectj) 风格）实现的。
- Join point: 程序执行过程中的一个点，例如一个方法的执行或一个异常的处理。在Spring AOP中，一个连接点总是代表一个方法的执行。
- Advice: 一个切面在一个特定的连接点采取的行动。不同类型的advice包括 "around"、"before" 和 "after" 的advice（Advice 类型将在后面讨论）。许多AOP框架，包括Spring，都将advice建模为一个拦截器，并在连接点（Join point）周围维护一个拦截器链。
- Pointcut: 一个匹配连接点的谓词（predicate）。advice与一个切点表达式相关联，并在切点匹配的任何连接点上运行（例如，执行一个具有特定名称的方法）。由切点表达式匹配的连接点概念是AOP的核心，Spring默认使用AspectJ的切点表达式语言。
- Introduction: 代表一个类型声明额外的方法或字段。Spring AOP允许你为任何 advice 的对象引入新的接口（以及相应的实现）。例如，你可以使用引入来使一个bean实现 `IsModified` 接口，以简化缓存。（介绍在AspectJ社区中被称为类型间声明）。
- Target object: 被一个或多个切面所 advice 的对象。也被称为 "advised object"。由于Spring AOP是通过使用运行时代理来实现的，这个对象总是一个被代理的对象。
- AOP proxy: 一个由AOP框架创建的对象，以实现切面契约（advice 方法执行等）。在Spring框架中，AOP代理是一个JDK动态代理或CGLIB代理。
- Weaving（织入）: 将aspect与其他应用程序类型或对象连接起来，以创建一个 advice 对象。这可以在编译时（例如，使用AspectJ编译器）、加载时或运行时完成。Spring AOP和其他纯Java AOP框架一样，在运行时进行织入。

- Spring AOP包括以下类型的advice。
  - Before advice: 在连接点之前运行的Advice ，但它不具备以下能力 阻止执行流进行到 join point 的能力（除非它抛出一个异常）。
  - After returning advice: 在一个连接点正常完成后运行的Advice （例如，如果一个方法返回时没有抛出一个异常）。
  - After (finally) advice: 无论连接点以何种方式退出（正常或特殊返回），都要运行该advice。
  - Around advice: 围绕一个连接点的advice，如方法调用。这是最强大的一种advice。Around advice可以在方法调用之前和之后执行自定义行为。它还负责选择是否继续进行连接点或通过返回自己的返回值或抛出一个异常来缩短advice方法的执行。

#### 5.2. Spring AOP 的能力和目标

#### 5.3. AOP 代理

- Spring AOP默认使用标准的JDK动态代理进行AOP代理。也可以使用CGLIB代理。

#### 5.4. @AspectJ 的支持

- `@AspectJ` 指的是将aspect作为带有注解的普通Java类来声明的一种风格。

##### 5.4.1. 启用 @AspectJ 的支持

- `@AspectJ` 支持可以通过XML或Java风格的配置来启用。

```java
@Configuration
@EnableAspectJAutoProxy
public class AppConfig {
}
```

##### 5.4.2. 声明一个 Aspect

- 在Spring AOP中，切面本身不能成为其他切面的advice的目标。

```xml
<bean id="myAspect" class="com.xyz.NotVeryUsefulAspect">
    <!-- configure properties of the aspect here -->
</bean>
```

```java
package com.xyz;
@Component
import org.aspectj.lang.annotation.Aspect;

@Aspect
public class NotVeryUsefulAspect {
}
```

##### 5.4.3. 声明一个切点（Pointcut）

```java
@Pointcut("execution(* transfer(..))") // the pointcut expression
private void anyOldTransfer() {} // the pointcut signature
```

- 完整的AspectJ点式语言支持Spring不支持的其他点式指定符：`call`、`get`、`set`、`preinitialization`、`staticinitialization`、`initialization`、`handler`、`adviceexecution`、`withincode`、`cflow`、`cflowbelow`、`if`、`@this` 和 `@withincode`。在由Spring AOP解释的pointcut表达式中使用这些 pointcut 指定器会导致抛出 `IllegalArgumentException`。
- 由于Spring的AOP框架是基于代理的，根据定义，目标对象内部的调用是不会被拦截的。对于JDK代理，只有代理上的public接口方法调用可以被拦截。
- 使用CGLIB，代理上的public和protected的方法调用都可以被拦截
- Spring AOP还支持一个额外的名为 `bean` 的PCD。ean PCD也可以和 `&&`（和）、`||`（或）、以及 `!` （否定） 操作符一起使用。

```java
bean(idOrNameOfBean)
```

###### Spring AOP支持的 `Pointcut` 指定器（PCD）

- `execution`: 用于匹配方法执行的连接点。这是在使用Spring AOP时要使用的主要切点指定器。
- `within`: 将匹配限制在某些类型内的连接点（使用Spring AOP时，执行在匹配类型内声明的方法）。
- `this`: 将匹配限制在连接点（使用Spring AOP时方法的执行），其中bean引用（Spring AOP代理）是给定类型的实例。
- `target`: 将匹配限制在连接点（使用Spring AOP时方法的执行），其中目标对象（被代理的应用程序对象）是给定类型的实例。
- `args`: 将匹配限制在连接点（使用Spring AOP时方法的执行），其中参数是给定类型的实例。
- `@target`: 限制匹配到连接点（使用Spring AOP时方法的执行），其中执行对象的类有一个给定类型的注解。
- `@args`: 将匹配限制在连接点（使用Spring AOP时方法的执行），其中实际传递的参数的运行时类型有给定类型的注解。
- `@within`: 将匹配限制在具有给定注解的类型中的连接点（使用Spring AOP时，执行在具有给定注解的类型中声明的方法）。
- `@annotation`: 将匹配限制在连接点的主体（Spring AOP中正在运行的方法）具有给定注解的连接点上。

###### 组合切点（Pointcut）表达式

- 可以通过使用 `&&`、`||` 和 `!` 来组合 pointcut 表达式。
- 从较小的命名的切点程序中建立更复杂的切点程序表达式是一种**最佳做法**

```java
package com.xyz;

@Aspect
public class Pointcuts {
	//如果一个方法执行连接点代表任何public方法的执行，则 publicMethod 匹配。
    @Pointcut("execution(public * *(..))")
    public void publicMethod() {} 
	//inTrading 匹配一个方法的执行是否在trading模块中。
    @Pointcut("within(com.xyz.trading..*)")
    public void inTrading() {} 
	//如果一个方法的执行代表了trading模块中的任何public方法，则 tradingOperation 匹配
    @Pointcut("publicMethod() && inTrading()")
    public void tradingOperation() {} 
}
```

###### 共享命名切点的定义

```java
package com.xyz;

import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Pointcut;

@Aspect
public class CommonPointcuts {

    /**
     * A join point is in the web layer if the method is defined
     * in a type in the com.xyz.web package or any sub-package
     * under that.
     */
    @Pointcut("within(com.xyz.web..*)")
    public void inWebLayer() {}

    /**
     * A join point is in the service layer if the method is defined
     * in a type in the com.xyz.service package or any sub-package
     * under that.
     */
    @Pointcut("within(com.xyz.service..*)")
    public void inServiceLayer() {}

    /**
     * A join point is in the data access layer if the method is defined
     * in a type in the com.xyz.dao package or any sub-package
     * under that.
     */
    @Pointcut("within(com.xyz.dao..*)")
    public void inDataAccessLayer() {}

    /**
     * A business service is the execution of any method defined on a service
     * interface. This definition assumes that interfaces are placed in the
     * "service" package, and that implementation types are in sub-packages.
     *
     * If you group service interfaces by functional area (for example,
     * in packages com.xyz.abc.service and com.xyz.def.service) then
     * the pointcut expression "execution(* com.xyz..service.*.*(..))"
     * could be used instead.
     *
     * Alternatively, you can write the expression using the 'bean'
     * PCD, like so "bean(*Service)". (This assumes that you have
     * named your Spring service beans in a consistent fashion.)
     */
    @Pointcut("execution(* com.xyz..service.*.*(..))")
    public void businessService() {}

    /**
     * A data access operation is the execution of any method defined on a
     * DAO interface. This definition assumes that interfaces are placed in the
     * "dao" package, and that implementation types are in sub-packages.
     */
    @Pointcut("execution(* com.xyz.dao.*.*(..))")
    public void dataAccessOperation() {}

}
```

- 可以通过引用 `@Aspect` 类的全称名称和 `@Pointcut` 方法的名称，在任何你需要切面表达式的地方引用在这样的切面定义。

```xml
<aop:config>
    <aop:advisor
        pointcut="com.xyz.CommonPointcuts.businessService()"
        advice-ref="tx-advice"/>
</aop:config>

<tx:advice id="tx-advice">
    <tx:attributes>
        <tx:method name="*" propagation="REQUIRED"/>
    </tx:attributes>
</tx:advice>
```

###### 示例

```java
execution(modifiers-pattern?
            ret-type-pattern
            declaring-type-pattern?name-pattern(param-pattern)
            throws-pattern?)
```

- 返回类型模式，前面片段中的 `ret-type-pattern`。`*` 是最常被用作返回类型模式的。它匹配任何返回类型。
- 名称模式匹配方法名称。你可以使用 `*` 通配符作为名称模式的全部或部分。如果你指定了一个声明类型模式，包括一个尾部的 `.` 来连接它和名称模式组件
- 参数模式稍微复杂一些：`()` 匹配一个不需要参数的方法，而 `(..)` 匹配任何数量（零或更多）的参数。 `(*)` 模式匹配一个需要任何类型的参数的方法。`(*,String)` 匹配一个需要两个参数的方法。第一个参数可以是任何类型，而第二个参数必须是一个 `String`。

###### 写出好的切点（Pointcuts）

- 现有的指定器自然分为三组之一：种类、范围（scope）和上下文。
  - 种类指定器选择了一个特定种类的连接点：`execution`、`get`、`set`、`call` 和 `handler`。
  - Scope 指定器选择了一组感兴趣的连接点（可能有许多种）：`within` 和 `withincode`。
  - 上下文指定器根据上下文进行匹配（并可选择绑定）：`this`、`target` 和 `@annotation`。

- 一个写得好的pointcut应该至少包括前两种类型（种类和范围）

##### 5.4.4. 声明 Advice

###### Before Advice

```java
@Aspect
public class BeforeExample {

    @Before("execution(* com.xyz.dao.*.*(..))")
    public void doAccessCheck() {
        // ...
    }
}
```

```java
@Aspect
public class BeforeExample {

    @Before("com.xyz.CommonPointcuts.dataAccessOperation()")
    public void doAccessCheck() {
        // ...
    }
}
```

###### After Returning Advice

```java
@Aspect
public class AfterReturningExample {

    @AfterReturning("execution(* com.xyz.dao.*.*(..))")
    public void doAccessCheck() {
        // ...
    }
}
```

```java
@Aspect
public class AfterReturningExample {

    @AfterReturning(
        pointcut="execution(* com.xyz.dao.*.*(..))",
        returning="retVal")
    public void doAccessCheck(Object retVal) {
        // ...
    }
}
```

###### After Throwing Advice

- 注意，`@AfterThrowing` 并不表示一般的异常处理回调。具体来说，`@AfterThrowing` advice方法只应该接收来自连接点（用户声明的目标方法）本身的异常，而不是来自附带的 `@After`/`@AfterReturning` 方法。

```java
@Aspect
public class AfterThrowingExample {

    @AfterThrowing("execution(* com.xyz.dao.*.*(..))")
    public void doRecoveryActions() {
        // ...
    }
}
```

```java
@Aspect
public class AfterThrowingExample {

    @AfterThrowing(
        pointcut="execution(* com.xyz.dao.*.*(..))",
        throwing="ex")
    public void doRecoveryActions(DataAccessException ex) {
        // ...
    }
}
```

###### After (Finally) Advice

```java
@Aspect
public class AfterFinallyExample {

    @After("execution(* com.xyz.dao.*.*(..))")
    public void doReleaseLock() {
        // ...
    }
}
```

###### Around Advice

```java
@Aspect
public class AroundExample {

    @Around("execution(* com.xyz..service.*.*(..))")
    public Object doBasicProfiling(ProceedingJoinPoint pjp) throws Throwable {
        // start stopwatch
        Object retVal = pjp.proceed();
        // stop stopwatch
        return retVal;
    }
}
```

###### Advice 参数

- 访问当前的 `JoinPoint`
  - `getArgs()`: 返回方法的参数。
  - `getThis()`: 返回代理对象。
  - `getTarget()`: 返回目标对象。
  - `getSignature()`: 返回正在被 advice 的方法的描述。
  - `toString()`: 打印对所 advice 的方法的有用描述。

- 向 Advice 传递参数
  - pointcut 表达式的 `args(account,..)` 部分有两个作用。首先，它将匹配限制在方法的执行上，即方法至少需要一个参数，并且传递给该参数的参数是一个 `Account` 的实例。其次，它使实际的 `Account` 对象通过 `account` 参数对 advice 可用。

  ```java
  @Before("execution(* com.xyz.dao.*.*(..)) && args(account,..)")
  public void validateAccount(Account account) {
      // ...
  }
  @Before("accountDataAccessOperation(account)")
  public void validateAccount(Account account) {
      // ...
  }
  ```

  - 引用 “[组合切点（Pointcut）表达式](https://springdoc.cn/spring/core.html#aop-pointcuts-combining)” 中定义的 `publicMethod` 命名的 pointcut。

  ```java
  @Before("com.xyz.Pointcuts.publicMethod() && @annotation(auditable)") 
  public void audit(Auditable auditable) {
      AuditCode code = auditable.value();
      // ...
  }
  ```

  - Advice 参数和泛型

  ```java
  @Before("execution(* ..Sample+.sampleGenericMethod(*)) && args(param)")
  public void beforeSampleMethod(MyType param) {
      // Advice implementation
  }
  ```
  - 确定参数名称
    - 看不懂
  - 明确的参数名称
    - `@AspectJ` advice 和 pointcut 注解有一个可选的 `argNames` 属性，你可以用它来指定被注解方法的参数名称。

  ```java
  @Before(
      value = "com.xyz.Pointcuts.publicMethod() && target(bean) && @annotation(auditable)", 
      argNames = "bean,auditable") 
  public void audit(Object bean, Auditable auditable) {
      AuditCode code = auditable.value();
      // ... use code and bean
  }
  ```

  - 使用参数进行调用

  ```java
  @Around("execution(List<Account> find*(..)) && " +
          "com.xyz.CommonPointcuts.inDataAccessLayer() && " +
          "args(accountHolderNamePattern)") 
  public Object preProcessQueryPattern(ProceedingJoinPoint pjp,
          String accountHolderNamePattern) throws Throwable {
      String newPattern = preProcess(accountHolderNamePattern);
      return pjp.proceed(new Object[] {newPattern});
  }
  ```

  - Advice 顺序
  - 优先级最高的advice在 "进入" 时首先运行（因此，给定两个 before advice，优先级最高的那个先运行）。
    - 从一个连接点 "出去" 时，优先级最高的advice最后运行（所以，给定两个 after advice，优先级最高的advice将第二运行）。
    - 通过在切面类中实现 `org.springframework.core.Ordered` 接口或用 `@Order` 注解来确定顺序。较低值的切面（或注解值）具有较高的优先权。
    - `@Around`, `@Before`, `@After`, `@AfterReturning`, `@AfterThrowing`。然而，请注意，`@After` advice 方法将在同一切面的任何 `@AfterReturning` 或 `@AfterThrowing` advice方法之后有效地被调用，遵循AspectJ对 `@After` 的 "after finally advice" 语义。

##### 5.4.5. Introduction

- 可以通过使用 `@DeclareParents` 注解来做一个introduction。这个注解被用来声明匹配的类型有一个新的父类（因此而得名）。

```java
@Aspect
public class UsageTracking {

    @DeclareParents(value="com.xyz.service.*+", defaultImpl=DefaultUsageTracked.class)
    public static UsageTracked mixin;

    @Before("execution(* com.xyz..service.*.*(..)) && this(usageTracked)")
    public void recordUsage(UsageTracked usageTracked) {
        usageTracked.incrementUseCount();
    }

}
```

##### 5.4.6. Aspect 实例化模式

- 高级不学了

##### 5.4.7. 一个AOP实例

```java
@Aspect
public class ConcurrentOperationExecutor implements Ordered {

    private static final int DEFAULT_MAX_RETRIES = 2;

    private int maxRetries = DEFAULT_MAX_RETRIES;
    private int order = 1;

    public void setMaxRetries(int maxRetries) {
        this.maxRetries = maxRetries;
    }

    public int getOrder() {
        return this.order;
    }

    public void setOrder(int order) {
        this.order = order;
    }

    @Around("com.xyz.CommonPointcuts.businessService()") 
    public Object doConcurrentOperation(ProceedingJoinPoint pjp) throws Throwable {
        int numAttempts = 0;
        PessimisticLockingFailureException lockFailureException;
        do {
            numAttempts++;
            try {
                return pjp.proceed();
            }
            catch(PessimisticLockingFailureException ex) {
                lockFailureException = ex;
            }
        } while(numAttempts <= this.maxRetries);
        throw lockFailureException;
    }
}
```

#### 5.5. 基于Schema的AOP支持

- 老旧、忽略

#### 5.6. 选择使用哪种AOP声明风格

- 忽略

#### 5.7. 混合切面类型

#### 5.8. 代理机制

- Spring AOP使用JDK动态代理或CGLIB来为特定的目标对象创建代理。JDK动态代理是内置于JDK中的，而CGLIB是一个普通的开源类定义库（重新打包到 `spring-core` 中）。
- 使用CGLIB，`final` 方法不能被advice，因为它们不能在运行时生成的子类中被重写。
- 如果要代理的目标对象至少实现了一个接口，就会使用JDK动态代理。目标类型实现的所有接口都被代理了。
- 如果目标对象没有实现任何接口，就会创建一个CGLIB代理。
- 要强制使用 CGLIB 代理，请将 `<aop:config>` 元素的 `proxy-target-class` 属性的值设为 `true`
- 当你使用@AspectJ自动代理支持时，要强制CGLIB代理，请将 `<aop:aspectj-autoproxy>` 元素的 `proxy-target-class` 属性设置为 `true`

##### 5.8.1. 了解AOP代理

- Spring AOP是基于代理的。
- 一旦调用最终到达目标对象（本例中的 `SimplePojo` 引用），它可能对自身进行的任何方法调用，如 `this.bar()` 或 `this.foo()`，都将被调用到 `this` 引用，而不是代理。**AspectJ不存在这种自我调用的问题，因为它不是一个基于代理的AOP框架。**

#### 5.9. 程序化创建@AspectJ代理

#### 5.10. 在Spring应用程序中使用AspectJ

- spring-aspects.jar

##### 5.10.1. 使用AspectJ对Spring的domain对象进行依赖注入

- `@Configurable` 注解标志着一个类有资格进行Spring驱动的配置。当以这种方式用作标记接口时，Spring通过使用与全称类型名称（`com.xyz.domain.Account`）相同的bean定义（通常是prototype范围）来配置被注解类型（本例中为 `Account`）的新实例。
- 可以指定 `@Configurable(autowire=Autowire.BY_TYPE)` 或 `@Configurable(autowire=Autowire.BY_NAME)` 
- `@Configurable(autowire=Autowire.BY_NAME,dependencyCheck=true)`来启用Spring对新创建和配置的对象中的对象引用的依赖性检查。如果这个属性被设置为 `true`，Spring会在配置后验证所有的属性（不是基本类型或集合）是否已经被设置
- @configurable的配置是在对象初始化之后进行的。`@Configurable(preConstruction = true)`让依赖关系在构造函数体运行之前被注入，从而可以在构造函数体中使用

##### 5.10.2. 用于 AspectJ 的其他 Spring 切面

- 忽略

##### 5.10.3. 使用 Spring IoC 配置 AspectJ Aspects

- 忽略

##### 5.10.4. 在Spring框架中用AspectJ进行加载时织入（Load-time Weaving）

- 忽略

### 6. Spring AOP API

- AOP基础开发不涉及，有权有势的开发才能做，一般做的话会影响所有人，造成负面影响。

#### 6.1. Spring中的Pointcut API

#### 6.2 spring 的advice API

#### 6.4. 使用 `ProxyFactoryBean` 创建AOP代理

### 7.  NULL-safety

- [`@Nullable`](https://docs.spring.io/spring-framework/docs/6.0.8-SNAPSHOT/javadoc-api/org/springframework/lang/Nullable.html): 注解，表明一个特定的参数、返回值或字段可以是 `null` 的。
- [`@NonNull`](https://docs.spring.io/spring-framework/docs/6.0.8-SNAPSHOT/javadoc-api/org/springframework/lang/NonNull.html): 注解表明特定的参数、返回值或字段不能为 `null`（在参数/返回值和字段上不需要，因为 `@NonNullApi` 和 `@NonNullFields` 分别适用）。
- [`@NonNullApi`](https://docs.spring.io/spring-framework/docs/6.0.8-SNAPSHOT/javadoc-api/org/springframework/lang/NonNullApi.html): 包级的注解，声明非null为参数和返回值的默认语义。
- [`@NonNullFields`](https://docs.spring.io/spring-framework/docs/6.0.8-SNAPSHOT/javadoc-api/org/springframework/lang/NonNullFields.html): 在包一级的注解，声明非null为字段的默认语义。

### 8. Data Buffer 和编解码器

- [`DataBufferFactory`](https://springdoc.cn/spring/core.html#databuffers-factory) 对数据缓冲区的创建进行了抽象。
- [`DataBuffer`](https://springdoc.cn/spring/core.html#databuffers-buffer) 代表一个字节缓冲区，它可以被 [池化 （pooled）](https://springdoc.cn/spring/core.html#databuffers-buffer-pooled)。
- [`DataBufferUtils`](https://springdoc.cn/spring/core.html#databuffers-utils) 为数据缓冲区提供实用方法。
- [编解码器（Codecs）](https://springdoc.cn/spring/core.html#codecs) 将数据缓冲流解码或编码为更高层次的对象。

#### 8.1 `DataBufferFactory`

#### 8.2. `DataBuffer`

#### 8.3. `PooledDataBuffer`

#### 8.4. `DataBufferUtils`

#### 8.5. 编解码器（Codecs）

#### 8.6. 使用 `DataBuffer`

### 9. 日志（Logging）

- 自Spring Framework 5.0以来，Spring在 `spring-jcl` 模块中实现了自己的Commons Logging bridge。该实现会检查classpath中是否存在Log4j 2.x API和SLF4J 1.7 API，并使用其中第一个发现的API作为日志实现，如果Log4j 2.x和SLF4J都不可用，则退回到Java平台的核心日志设施（也被称为JUL或 `java.util.logging`）。

### 10. AOT 编译优化

### 11. 附录

#### 11.3. 应用程序的启动步骤

| *Table 15. 核心容器中定义的应用程序启动步骤*   |                                                              |                                                          |
| :--------------------------------------------- | :----------------------------------------------------------- | :------------------------------------------------------- |
| 名称                                           | 说明                                                         | 标签                                                     |
| `spring.beans.instantiate`                     | 实例化一个Bean及其依赖关系。                                 | `beanName` 是Bean的名字，`beanType` 是注入点需要的类型。 |
| `spring.beans.smart-initialize`                | `SmartInitializingSingleton` Bean的初始化。                  | `beanName` 是bean的名称。                                |
| `spring.context.annotated-bean-reader.create`  | 创建 `AnnotatedBeanDefinitionReader`.                        |                                                          |
| `spring.context.base-packages.scan`            | 扫描 base package。                                          | `packages` 是用于扫描的 base package 数组。              |
| `spring.context.beans.post-process`            | Bean 后处理阶段。                                            |                                                          |
| `spring.context.bean-factory.post-process`     | 调用 `BeanFactoryPostProcessor` bean。                       | `postProcessor` 当前后处理阶段。                         |
| `spring.context.beandef-registry.post-process` | 调用 `BeanDefinitionRegistryPostProcessor` bean.             | `postProcessor` 当前后处理阶段。                         |
| `spring.context.component-classes.register`    | 通过 `AnnotationConfigApplicationContext#register` 进行组件类（component class）的注册。 | `classes` 数组，用于注册给定的类。                       |
| `spring.context.config-classes.enhance`        | 用CGLIB代理增强配置类。                                      | `classCount` 增强类的数量。                              |
| `spring.context.config-classes.parse`          | 用 `ConfigurationClassPostProcessor` 进行配置类的解析阶段。  | `classCount` 已处理的类的数量。                          |
| `spring.context.refresh`                       | Application context 刷新阶段。                               |                                                          |










































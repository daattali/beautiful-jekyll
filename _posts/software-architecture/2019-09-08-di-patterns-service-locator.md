---
layout: post
title: DI Паттерны. Service Locator
category: software architecture
tags: [.net, development, design patterns]
---

- Источник [Блог Сергея Теплякова](http://sergeyteplyakov.blogspot.com/2013/03/di-service-locator.html) 
- Еще ссылка по теме [https://habr.com/post/270005/](https://habr.com/post/270005/)
- И еще кратко на SO: [https://stackoverflow.com/a/4985582](https://stackoverflow.com/a/4985582)

---

Сервис локатор – это очень неоднозначный паттерн проектирования. С одной стороны, именно с его появлением началось активное развитие DI контейнеров и практик инверсии управления. С другой стороны, именно благодаря повсеместному использованию сервис локаторов в приложениях техники управления зависимостями получили и продолжают получать столько критики.

Но прежде чем переходить к описанию достоинств и недостатков этого паттерна, давайте дадим его описание и общую структуру. 

### **Описание**

Суть паттерна Сервис Локатор сводится к тому, что вместо создания конкретных объектов («сервисов») напрямую с помощью ключевого слова **new**, мы будем использовать специальный «фабричный» объект, который будет отвечать за создание, а точнее «нахождение» всех сервисов.

![](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/962589c8-78a4-4217-9c81-933934b57678/image_thumb255B4255D.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=ASIAT73L2G45P3LWE2VG%2F20190817%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20190817T161354Z&X-Amz-Expires=86400&X-Amz-Security-Token=AgoJb3JpZ2luX2VjEMX%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJHMEUCIQCfAlc6LPSGAut5Gv59Kp%2BCG%2BVWtkay7XscXq%2FJkqwnuwIgYUUu0nTL8VGxkOrQ7lD%2BbWc%2BULrp%2BzQsXZKG8%2FH6Q20q2gMIXhAAGgwyNzQ1NjcxNDkzNzAiDAnGuTac4rt5wlj%2BWSq3A5vA1TWdJpPEsbU8C5qG1bxH6Wtfcv%2BauovN0aGnM5m8Rm%2BmfJh42kCew15cuXs8920YfFNn%2BUjxHYHy2BFz2oQcqB%2BuBrsIOmoSimxZIAMzP30z49WoUqIdELza9zrFngsvhVla5%2BsOzjuiAA6p2i%2FMYLXFf9nH29obcc61mRFrpqdoTHceeGZFD1TUrSUDxhZLYA6kFXwl0l8ar1FHW3SwXi6LP6P%2FaQekLScEpjqYx%2BeFqA4t%2BpOf4cGRXJhD%2FqozfnelKdReMEIHqSt7LU8o3iUnAGHvGWOZMdoFto5EYlhERrZT4RSaOF5sLPFeFjeTX2SGXbXTnBDGBiv9fbn6GRvF8bEGWpndY4XATMVb7FZRezpy9EqnotGu6gxlcmO88RwZYOO888CHvW86yQf0XQvKLNt2VoOju3e%2FDVgbFzs3XR7nGPatGDITD%2Fkekl76X4LqqNQEuujHYi47iSfWVqScSV2VLgBjwSOkUzJIuw68Ec8fQyt1V%2B2VbpN0qpB8ZCWWC0GWRtIIL%2Bpd78Vlivhx8y3wR8rS5TrlJHeoWVwjYDW5WyowUqvcOT9NNLQ1bjNWOUYw0%2BPf6gU6tAFVfy1IyMtzcw2bm1klq6gicc4Ss9DQz0dxdp7yfhqcNFvv9xL4ymQzZenHwrwK1f9TiK1OEskaWPUS3kLw7WJrBABCyC37M70EFbdKh4xcbGJDslwLyiRspt8phKDhTp%2F4RYLKFvIAhTPlLm6qRltNaN2NUjx1P11gdOyLGxH1DQm4RfypNxIc%2FrzFM0R6lBencqh%2BXLMtNRMsFOXKbs8%2Fio9n4F67GpkDbq9DXZWhAODTsgI%3D&X-Amz-Signature=d5ac9c2a2663a499fd46df7aa2cda7f0e7fd625815feb2dd1c97e84840d64318&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22image_thumb255B4255D.png%22)

    // Статический "локатор"
    public static class ServiceLocator
    {
    	public static object GetService(Type type) {}
    	public static T GetService<T>() {}
    }
    
    // Сервис локатор в виде интерфейса
    public interface IServiceLocator
    {
    	T GetService<T>();
    }

Сервис локатор может быть статическим классом с набором статических методов, или же может существовать в виде интерфейса для упрощения тестирования.

### **Назначение**

Разорвать жесткую связь между классом и его вспомогательными сервисами, путем добавления специального класса (локатора), который будет за это отвечать.

### **Применимость**

Прочитав описание и назначение этого паттерна, внимательный читатель заметит невероятное сходство Сервис Локатора со своим любимым DI контейнером. И правда, основная суть любого контейнера заключается в регистрации и последующего получения требуемых зависимостей, с рядом дополнительных свистелок, которые делают этот процесс более ~~сложным~~ удобным.

Однако между DI контейнером и его использованием в виде Сервис Локатора существует тонкая грань. По всем правилам, использование контейнера должно быть ограничено минимальным количеством мест. В идеале, в приложении должна быть лишь одна точка, где производится вызов метода **container.Resolve()**; этот код должен находиться либо в точке инициализации приложения (так называемый [Composition Root](http://sergeyteplyakov.blogspot.com/2013/01/blog-post.html#CompositionRoot)), либо максимально близко к ней.

Однако наличие в арсенале универсального объекта, способного получить любую зависимость, провоцирует к его использованию напрямую и в других частях приложения.

Предположим, нам во вью модели редактирования карточки сотрудника нам нужно обратиться к сервису из слоя доступа к данным. Мы можем протянуть нужную зависимость через конструктор, а можем просто передать этой вью модели сам контейнер, чтобы она получила требуемую зависимость самостоятельно:

    class EditEmployeeViewModel
    {
    	private Employee _employee;
    	private IServiceLocator _serviceLocator;
    
    	public EditEmployeeViewModel(IServiceLocator serviceLocator) 
    	{
    		_serviceLocator = serviceLocator;
    	}
    
    	private void OkCommandHandler()
    	{
    		ValidateEmployee(_employee);
    		var repository = _serviceLocator.GetService<IRepository>();
    		repository.Save(_employee);
    	}
    
    	private void ValidateEmployee(Employee employee) {}
    }

И хотя использование Сервис Локатора является довольно популярным, у него есть ряд ~~фатальных~~ существенных недостатков.

### **Недостатки Сервис Локатора**

Существует две версии реализации этого паттерна Сервис Локатора. Локатор сам по себе может быть синглтоном (в классическом виде, или в виде класса с набором статических методов), тогда доступ к нему может производиться из любой точки в коде. Или же Сервис Локатор может передаваться требуемым классам через конструктор или свойство в виде объекта класса или интерфейса.

Оба эти подхода страдают от одних и тех же недостатков, но в первом случае все нижеперечисленные проблемы усиливаются, поскольку в этом случае совершенно любой класс приложения может быть завязан на любой «сервис».

### **Неясный контракт класса**

Даже если вы не являетесь поклонником [контрактного программирования](http://sergeyteplyakov.blogspot.com/2010/05/design-by-contract.html) (а зря;)), вы наверняка ловили себя на мысли, что у любого класса есть две составляющие. С одной стороны, есть требования заказчика (клиента вашего класса): он хочет получить от класса некоторый результат (получить запись о пользователе из базы данных). С другой стороны, для выполнения этой работы класс имеет право требовать что-то от своего клиента (идентификатор пользователя, данные о котором нужно получить из базы данных).

В результате, между классом и его клиентом существует формальный или неформальный «контракт», который выражается в виде предусловий (требований к клиенту) и постусловий (гарантий выполнения работы). Однако если класс принимает экземпляр сервис локатора, или, хуже того, использует глобальный локатор, то этот контракт, а точнее требования, которые нужно выполнить клиенту класса, становятся неясными:

    class EditEmployeeViewModel
    {
    	private IServiceLocator _serviceLocator;
    	
    	public EditEmployeeViewModel(IServiceLocator serviceLocator)
    	{
    		_serviceLocator = serviceLocator;
    	}
    }

Как понять клиенту данного класса, что от него требуется для того, чтобы данный объект выполнил свою часть работы? Какие «предусловия» класса **EditEmployeeViewModel**? Наличие в сервис локаторе **IRepository**, **ILogger**, **IEMailSender**, **ISomethingElse**? Чтобы понять это нам придется проанализировать исходный код этого класса, что совсем не просто, а иногда еще и невозможно.

Кроме того, вполне возможно, что **EditEmployeeViewModel** не выполняет всю работу самостоятельно, а делегирует часть обязанностей другому классу, например, **DialogEditViewModel**. И уже этот класс получает нужную зависимость у Сервис Локатора для сохранения сотрудника. В результате, чтобы понять требования класса **EditEmployeeViewModel** придется проанализировать исходный код не только этого класса, но и всех зависимых классов.

![](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/84bdcfeb-dd04-40bd-a41e-03996c5b1d35/image_thumb255B8255D.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=ASIAT73L2G45FEZRN3DP%2F20190817%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20190817T161442Z&X-Amz-Expires=86400&X-Amz-Security-Token=AgoJb3JpZ2luX2VjEMX%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJHMEUCIFUdW97ZVSyZEYHnUglraQ%2BAM2BykMinx3RVqcLjVgfbAiEA2wwCkT10N1utvyrxS8RUreZ8oi4wEjpq9yQ355CZSMYq2gMIXhAAGgwyNzQ1NjcxNDkzNzAiDNWy%2BLPFDYkCA2bnHyq3AyADmhUJ5a%2BQfLAcCjKvW2pEEhsL5gu3EANMPENY7L4fziI5AJnkxaFIDKa0HKXLdG8zCXhLyiELefrzUU%2BjC%2BBo0hOy8jmWGhpa3TdPmmZbwj9uuuxQMiLNuHWZNGmaXRylvpBJdveyXR4xf5ejxTKDIWuVczDph9OQ0OnSrrc1TyCb8W%2FGyRZZVgS%2Bz3XsxQviFNwMA6q6djcSGozd2Vwr%2F0rYpPoj%2Fko9WNVwrvoRYLtsAmG%2BDc4PE9rGdMofTKLR0hLl4ozyQHBH9Rztwsmlerveakla2Uo73gu1hk6D5fJhBpJok6BJNHMrTYzCgz5d2v%2B%2FTNKtORy3%2FAvTVpZewgvkZP1Re2AqPrX7iLfcukzxVh%2F%2FzYBibq%2FQwlzQnzAFiYboysH9Ci%2FxoSvMiowq7QaD381iWYJQAGWj%2BhskCZtpCMBjNRc1VYbmg7dWqBTnJ6IjulC0y5AbjRcaFtBohJeSPN5EDLQ%2BrOBCDgop9fZondqFyPMVjAyuZw6THCX%2FnkJxS%2FJNPxpBiuJL2pJWGbGTGwmXkNmwpWTgzw%2F08KTAR56TB77bMbHn80%2BKx8VeaFU8rUUwh%2BXf6gU6tAEn3zMo6T%2BXHH%2BZIp08%2B4YEuferQpcvq8uA8%2FmdzjDL3pF5e%2B2FuFCN05ONoYGg8RN4EXlANAqzNLVMAMvff%2BIZU8roqhuvy9noSxUhFiM%2FGPXMdcS0KFNhEzyCV4X85WmkFxfyASsMzpRNRKhPwnpSOwpOzPBIe8WwfSqZmnXLOC8MU7RyEW0WxiCo%2FkDm1Fn78Fp041gQq%2FBtiLWU19Mkh4xmUPC0dJJ8ng9dHqUFYcTo3Nc%3D&X-Amz-Signature=8722c010d0f4a4b237b0227dbb5bfa2d2d75a727db36a6499ea0f692d08f6c44&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%22image_thumb255B8255D.png%22)

Если рассматривать это решение с точки [критериев хорошего дизайна](http://sergeyteplyakov.blogspot.com/2013/01/blog-post_29.html), то его дизайн явялется отвратительным, поскольку является жестким, хрупким и неподвижным. Внесение изменение в одной части системы (например, в нашем классе **DialogEditViewModel** или в любом классе, который он использует) приведет к необходимости изменения логики инициализации локатора. И такая «логическая связанность» приведет к непредвиденным ошибкам во время исполнения, поскольку рано или поздно мы забудем обновить одну часть системы, при изменении другой части и получим тот самый «эффект бабочки», которого мы так хотим избежать. Наконец, этот класс невероятно сложно использовать повторно, поскольку очень сложно понять, что же должно находиться в Локаторе для его нормальной работы.

### **Неопределенная сложность класса**

При описании [аксиомы управления зависимостями](http://sergeyteplyakov.blogspot.com/2013/02/blog-post.html) мы познакомились с [метрикой стабильности класса](http://sergeyteplyakov.blogspot.com/2013/02/blog-post.html#Metric), которая звучит так: нестабильность текущего класса прямо пропорциональна количеству сущностей, которые он использует. Конечно, это метрика не вполне точна и в реальности нужно как минимум учитывать [стабильность](http://sergeyteplyakov.blogspot.com/2012/11/blog-post.html#Stable) используемых зависимостей, тем не менее, это вполне неплохая отправная точка определения сложности класса.

Когда наш класс использует сервис локатор, то стабильность класса становится неопределенной. Наш класс, теоретически, может использовать что угодно, поэтому изменение любого класса (или интерфейса) в нашем проекте может затронуть произвольное количество классов и модулей.

Передача зависимостей через [конструктор](http://sergeyteplyakov.blogspot.com/2012/12/di-constructor-injection.html) позволяет нам четко видеть все необходимые зависимости, а их увеличение четко дает нам понять, что наш дизайн движется в неправильную сторону. Использование локатора дает видимость простоты дизайна даже в том случае, когда дизайн класса начинает «протухать». В результате мы можем упустить момент, а когда мы осознаем существование проблемы с дизайном, ее решение может оказаться слишком дорогостоящим.

**ПРИМЕЧАНИЕ**

Я не знаю, что может быть хуже неявной связности, которая приводит к неявной сложности. Если класс является сложным по своей природе, я стараюсь сделать все для того, чтобы это было ясно через призму его открытого интерфейса. Мы должны постараться спрятать эту сложность внутри класса, но если классу для его работы требуется десять зависимостей, то это требование должно быть явным.

### **Отсутствие строгой типизации**

Сервис локатор можем содержать несколько способов получения (или поиска) зависимостей:

    class Locator
    {
    // Не строготипизированное получение сервиса
    public object Resolve(Type type) { }
    
    // Якобы строготипизированное получение сервиса
    public T Resolve<T>() { }
    }

Многие склонны считать, что метод **Resolve**, возвращающий **object** является «слабо типизированным», в то время, как обобщенный метод **Resolve** обеспечивает строгую типизацию.

Как правильно [писал Эрик Липперт](http://blogs.msdn.com/b/ericlippert/archive/2012/10/15/is-c-a-strongly-typed-or-a-weakly-typed-language.aspx), проблема здесь в том, что понятие строгой типизации весьма размыто и даже в [Вики](http://en.wikipedia.org/wiki/Strong_typing) есть десяток разных определений. Да, обобщенный метод **Resolve** устраняет необходимость приведения типов (это приведение находится внутри этого метода;)), но ведь отсутствие явного приведения типов не является единственным свойством строгой типизации.

Главное преимущество строгой типизации – это раннее определение логических ошибок в приложении. При наличии строгой типизации мы переносим момент определения ошибок с этапа выполнения, на этап компиляции. Вот с этой точки зрения, обе версии метода **Resolve** являются одинаково «слабо типизированными», поскольку тот факт, что наш код компилируется совсем не означает, что он будет вести себя корректным образом во время исполнения.

**Смягчаем проблему**

Сейчас должно быть понятно, что от Сервис Локатора стоит держаться подальше, но что делать, если наше приложение уже активно его использует и избавиться от него не так и просто?

Существует два разных способа получения зависимостей у Сервис Локатора. Во-первых, мы можем получать необходимые зависимости по мере необходимости:

    class EditEmployeeViewModel
    {
    	private void OkCommandHandler()
    	{
    		ValidateEmployee(_employee);
    		var repository = _serviceLocator.GetService<IRepository>();
    		repository.Save(_employee);
    	}
    }

Это наиболее простой способ, который позволяет не получать дорогостоящие зависимости, если в них не возникла необходимость. Однако именно этот способ страдает всеми проблемами этого паттерна наиболее сильно, поскольку для того, чтобы узнать список зависимостей класса придется проанализировать реализацию каждого метода.

В качестве альтернативы, мы можем не ждать потребности в зависимостях до самого последнего момента, а получить их в конструкторе класса:

    class EditEmployeViewModel
    {
    	private readonly IRepository _repository;
    	private readonly ILogger _logger;
    	private readonly IMailSender _mailSender;
    	private readonly IServiceLocator _locator;
    	public EditEmployeViewModel(IServiceLocator locator) 
    	{
    		_locator = locator;
    		_repository = locator.GetService<IRepository>();
    		_mailSender = locator.GetService<IMailSender>();
    		_logger = locator.GetService<ILogger>();
    	}
    }

В этом случае мы жертвуем «ленивостью» получения зависимостей, но требуемые зависимости класса (и его сложность) становятся более очевидными. Кроме того, такой подход упрощает переход к передаче зависимостей через конструктор, поскольку это требует изменение лишь одного метода.

**Заключение**

Самое страшное в Сервис Локаторе то, что он дает видимость хорошего дизайна. У нас никто не знает о конкретных классах, все завязаны на интерфейсы, все «нормально» тестируется и «расширяется». Но когда вы попробуете использовать ваш код в другом контексте или когда кто-то попробует использовать его повторно, вы с ужасом поймете, что у вас есть дикая «логическая» связанность, о которой вы и не подозревали.

Для меня ясность и понятность интерфейса класса важнее количества параметров конструктора. Я не исключаю, что бывают случаи, когда сервис локатор является наименьшим злом, но я бы в любом случае постарался свести его использования к минимуму.

### **Дополнительные ссылки**

[Service Locator is an Anti-Pattern by Mark Seemann](http://blog.ploeh.dk/2010/02/03/ServiceLocatorisanAnti-Pattern/)
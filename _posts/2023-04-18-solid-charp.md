---
layout: post
title: SOLID Principles in C#: A Guide to Writing Robust and Maintainable Code
subtitle: Learn How to Write High-Quality Code with SOLID Principles in C#: Examples Included
tags: [solid, solid principles, c#, csharp, examples, srp, ocp, lsp, isp, dip]
comments: true
---

The SOLID principle is a set of guidelines that helps software developers build code that's simple to maintain, understand, and expand. It's an acronym for Single Responsibility, Open/Closed, Liskov Substitution, Interface Segregation, and Dependency Inversion principles. In this article, we'll delve into each of these principles in detail and showcase how to put them into practice using C# programming language.

**[S] - Single Responsibility Principle (SRP)**

The Single Responsibility Principle (SRP) states that each class should have only one responsibility. In other words, a class should only be responsible for one thing. This principle makes code easier to understand and maintain, as it avoids unnecessary complexity and confusion.

Let's take an example in C# to illustrate this principle. Imagine we have a CustomerRepository class that is responsible for managing the data access for the Customer entity in a database. It has three methods: Save, Update, and Delete.

```c#

public class CustomerRepository
{
    private readonly DbContext _dbContext;

    public CustomerRepository(DbContext dbContext)
    {
        _dbContext = dbContext;
    }

    public void Save(Customer customer)
    {
        _dbContext.Customers.Add(customer);
        _dbContext.SaveChanges();
    }

    public void Update(Customer customer)
    {
        _dbContext.Entry(customer).State = EntityState.Modified;
        _dbContext.SaveChanges();
    }

    public void Delete(int id)
    {
        var customer = _dbContext.Customers.Find(id);
        _dbContext.Customers.Remove(customer);
        _dbContext.SaveChanges();
    }
}

```

In this example, the CustomerRepository class is responsible for one thing only, which is managing data access for the Customer entity. It has a clear and concise purpose, making it easier to understand and maintain. However, if we add additional responsibilities, such as calculating a customer's total purchases or sending email notifications, then the class becomes more complex and harder to maintain. Therefore, it's important to create separate classes for each responsibility, adhering to the Single Responsibility Principle.

**[O] - Open/Closed Principle (OCP)**

The Open/Closed Principle (OCP) states that software entities (classes, modules, functions, etc.) should be open for extension but closed for modification. In other words, you should be able to add new functionality to a system without changing existing code.

Let's continue with the example of the CustomerRepository class in C# to illustrate this principle. Suppose we want to add a new functionality that allows us to retrieve customers from a web API instead of a database. Instead of modifying the existing CustomerRepository class, we can create a new class that implements the same interface as the CustomerRepository class but uses a different data source.

```c#

public interface ICustomerRepository
{
    void Save(Customer customer);
    void Update(Customer customer);
    void Delete(int id);
}

public class CustomerRepository : ICustomerRepository
{
    private readonly DbContext _dbContext;

    public CustomerRepository(DbContext dbContext)
    {
        _dbContext = dbContext;
    }

    public void Save(Customer customer)
    {
        _dbContext.Customers.Add(customer);
        _dbContext.SaveChanges();
    }

    public void Update(Customer customer)
    {
        _dbContext.Entry(customer).State = EntityState.Modified;
        _dbContext.SaveChanges();
    }

    public void Delete(int id)
    {
        var customer = _dbContext.Customers.Find(id);
        _dbContext.Customers.Remove(customer);
        _dbContext.SaveChanges();
    }
}

public class ApiCustomerRepository : ICustomerRepository
{
    private readonly HttpClient _httpClient;

    public ApiCustomerRepository(HttpClient httpClient)
    {
        _httpClient = httpClient;
    }

    public void Save(Customer customer)
    {
        throw new NotImplementedException();
    }

    public void Update(Customer customer)
    {
        throw new NotImplementedException();
    }

    public void Delete(int id)
    {
        throw new NotImplementedException();
    }
}

```

In this example, we created a new class called ApiCustomerRepository that implements the ICustomerRepository interface. We can now use this class to retrieve customers from a web API instead of a database without modifying the existing code. This adheres to the Open/Closed Principle, as we are able to extend the functionality of the system without changing the existing code.

**[L] - Liskov Substitution Principle (LSP)**

The Liskov Substitution Principle (LSP) states that if a program is using a base class, it should be able to use any of its derived classes without knowing it. In other words, a derived class should be substitutable for its base class without causing errors or unexpected behavior.

Continuing with the example of the CustomerRepository class in C#, let's suppose we have a derived class called InMemoryCustomerRepository that stores customer data in memory instead of a database. This class should be substitutable for the base CustomerRepository class, as they both implement the ICustomerRepository interface.

```c#

public class InMemoryCustomerRepository : ICustomerRepository
{
    private List<Customer> _customers = new List<Customer>();

    public void Save(Customer customer)
    {
        _customers.Add(customer);
    }

    public void Update(Customer customer)
    {
        var existingCustomer = _customers.FirstOrDefault(c => c.Id == customer.Id);
        if (existingCustomer != null)
        {
            existingCustomer.Name = customer.Name;
        }
    }

    public void Delete(int id)
    {
        var customer = _customers.FirstOrDefault(c => c.Id == id);
        if (customer != null)
        {
            _customers.Remove(customer);
        }
    }
}

```

In this example, the InMemoryCustomerRepository class is substitutable for the CustomerRepository class, as it implements the same ICustomerRepository interface and provides the same functionality. We can now use either class interchangeably without causing errors or unexpected behavior, adhering to the Liskov Substitution Principle.

**[I] - Interface Segregation Principle (ISP)**

The Interface Segregation Principle (ISP) states that classes should not be forced to implement interfaces they don't use. In other words, a class should only depend on the interfaces that it actually needs, and not on any additional ones that it doesn't.

Let's continue with the example of the CustomerRepository class in C# to illustrate this principle. Suppose we have another interface called IOrderRepository that defines methods for managing orders in a database.

```c#

public interface IOrderRepository
{
    void Save(Order order);
    void Update(Order order);
    void Delete(int id);
}

```

If we were to implement this interface in the CustomerRepository class, it would violate the ISP because the CustomerRepository class doesn't need to manage orders. Instead, we can split the ICustomerRepository interface into smaller interfaces, each with its own set of methods.

```c#

public interface ICustomerSaver
{
    void Save(Customer customer);
}

public interface ICustomerUpdater
{
    void Update(Customer customer);
}

public interface ICustomerDeleter
{
    void Delete(int id);
}

public interface ICustomerRepository : ICustomerSaver, ICustomerUpdater, ICustomerDeleter
{
    // Methods specific to customer repository go here
}

```

In this example, we split the ICustomerRepository interface into three smaller interfaces that each define a single responsibility. The ICustomerRepository interface then inherits from these smaller interfaces. This adheres to the Interface Segregation Principle because each class can now depend only on the interfaces that it actually needs, without being forced to implement any additional methods that it doesn't need.

**[D] - Dependency Inversion Principle (DIP)**

The Dependency Inversion Principle (DIP) states that high-level modules should not depend on low-level modules, but both should depend on abstractions. In other words, classes should depend on abstract interfaces rather than concrete implementations.

To illustrate this principle using the CustomerRepository class in C#, let's suppose that the CustomerService class depends on the concrete CustomerRepository class to access the database.

```c#

public class CustomerService
{
    private CustomerRepository _repository;

    public CustomerService()
    {
        _repository = new CustomerRepository();
    }

    public void Save(Customer customer)
    {
        _repository.Save(customer);
    }

    public void Update(Customer customer)
    {
        _repository.Update(customer);
    }

    public void Delete(int id)
    {
        _repository.Delete(id);
    }
}

```

In this example, the CustomerService class is directly dependent on the CustomerRepository class, which violates the DIP. To adhere to the DIP, we should introduce an abstraction between the CustomerService and CustomerRepository classes.

```c#

public interface ICustomerRepository
{
    void Save(Customer customer);
    void Update(Customer customer);
    void Delete(int id);
}

public class CustomerService
{
    private ICustomerRepository _repository;

    public CustomerService(ICustomerRepository repository)
    {
        _repository = repository;
    }

    public void Save(Customer customer)
    {
        _repository.Save(customer);
    }

    public void Update(Customer customer)
    {
        _repository.Update(customer);
    }

    public void Delete(int id)
    {
        _repository.Delete(id);
    }
}

```

In this modified example, we introduced an interface called ICustomerRepository that the CustomerRepository class now implements. The CustomerService class is now dependent on the abstraction, rather than the concrete implementation of the repository. This adheres to the DIP because the CustomerService class now depends on an abstraction, rather than a concrete implementation.

**Conclusion**

In conclusion, the SOLID principles are a set of guidelines for software development that emphasize the importance of building code that is easy to maintain, understand, and extend. By following these principles, developers can create software that is flexible, robust, and easy to change.

In this article, we discussed each of the SOLID principles in detail, along with code examples in C# to demonstrate how to implement them.

The Single Responsibility Principle (SRP) emphasizes the importance of ensuring that a class has only one responsibility. We demonstrated this principle using the example of a Customer class that had a single responsibility for storing customer data.

The Open/Closed Principle (OCP) encourages developers to write code that is open for extension but closed for modification. We demonstrated this principle using the example of a CustomerRepository class that used interfaces and abstract classes to allow for extension without modification.

The Liskov Substitution Principle (LSP) emphasizes the importance of ensuring that derived classes can be used interchangeably with their base classes. We demonstrated this principle using the example of a CustomerRepository class that correctly implemented the LSP by following the contract of its base class.

The Interface Segregation Principle (ISP) states that classes should not be forced to implement interfaces they don't use. We demonstrated this principle using the example of a CustomerRepository class that split its interface into smaller, more focused interfaces to avoid forcing implementers to implement unnecessary methods.

Finally, the Dependency Inversion Principle (DIP) emphasizes the importance of depending on abstractions rather than concrete implementations. We demonstrated this principle using the example of a CustomerService class that depended on the abstraction of an ICustomerRepository interface, rather than the concrete implementation of a CustomerRepository class.

By following these SOLID principles, developers can write code that is flexible, extensible, and easy to change. By adhering to these principles, developers can create software that is easy to maintain, understand, and extend, resulting in a more robust and flexible codebase that can better adapt to changing requirements over time.
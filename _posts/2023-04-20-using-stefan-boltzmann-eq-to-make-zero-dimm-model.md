---
layout: post
title: Using the stefan-boltzmann equation to create a zero-dimensional climate model.
subtitle: Using the stefan-boltzmann equation and simple algebra the temperature of a "naked" earth can be easily solved for.
# cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/earth.jpg
# share-img: /assets/img/path.jpg
tags: [modeling, climate]
---
As objects get hotter they lose energy quicker. This simple fact is known intuitively to any human being who has touched a hot pan by accident and used cold water to alleviate the pain. While in this scenario the heat is being transferred through physical contacts of the systems involved, in space the same holds true however the bulk if heat is transferred in the form of radiation. The governing equation of radiation emission is:

$$\epsilon * \sigma * T^4$$

But what do those variables represent?\

- _epsilon_ ($\epsilon$): blackbody constant (how good the system is at radiating heat back out) 
- _sigma_ ($\sigma$): the stefan-boltzmann constant (a value found through experimentation)
- _T_:  temperature (in K)\

The units of the final result are $W/m^2$ (sometimes written as $W*m^-2$), which lends a clue as to what the equation represents. 

> Note: Watts are a unit that stands for Joules per second, so it is a measure of energy flow over time. This is akin to how you would measure the flow of a river in gallons per minute; measuring it in gallons without specifying a time period doesn't make sense!

The equation tells us how many watts per square meter the system is radiating, so if you were to imagine taking the skin off of the system (in this case imagine a sphere) and laying it flat on the ground each square meter of the system would be radiating a certain amount of energy per second (watts). 

Ex. If the value of the stefan-boltzmann equation for a cube were 5 $W*m^-2$ then after laying out the cube's skin on the floor each square meter would radiate (on average) 5 joules every second!

So, how can we use this to build a climate model? 

Given that the radiative forcing of the sun on the earth (the amount of heat being added to the earth through radiation from the sun) is equal to $\frac{L(1-\alpha)}{4}$ where $L$ and $\alpha$ are the solar constant (the average W/m^2 given off in radiation by the sun to the earth) and the albedo (reflectiveness, energy reflected is lost) of the earth respectively we can solve for the temperature of a "naked" earth. (Read the derivation of that: here)

{: .box-note}
A naked earth means that we are not simulating the greenhouse gas layer or atmosphere

It is helpful to begin what it means when an object has a "temperature" in the first place. One way to picture an object at a stable temperature is to see it constantly losing and gaining energy. Then, it can be said that an object is at a stable temperature when these two values are equal. With that in mind, the temperature of the earth, just like any thermodynamically-bound body, will settle when it loses as much energy as it gains, so the forcing due to the sun must be equal to the flux of the earth, therefore:

$$\frac{L(1-\alpha)}{4} = \epsilon * \sigma * T^4$$


Using this equation, we can isolate T…

$$T = \left [ \frac{L(1-\alpha)}{4 * \sigma * \epsilon} \right ] ^ \frac{1}{4}$$

and solve! 


Try solving for the temperature of the naked earth yourself by global averages of:\

| Variable | Global Avg. Val. | Units                     |
|----------|------------------|---------------------------|
| L        | 1340             | W/m^2                     |
| Albedo   | .3               | n/a                       |
| Sigma    | 5.67 * 10^-8     | $W \cdot m^-2 \cdot K^-4$ |
| Epsilon  | 1                | n/a                       |

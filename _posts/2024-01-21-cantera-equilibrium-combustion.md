---
layout: post
title: Visualizing & Animating Equilibrium Combustion Products vs. Equivalence Ratio 
subtitle: Using Cantera and Plotly Animations
gh-repo: cormazz/vmd-denoising
gh-badge: [star, fork, follow]
tags: [python, cantera, combustion, Georgia Tech, plotly, animation]
comments: true
author: Corrado R. Mazzarelli
---

* Do not remove this line (it will not be displayed)
{:toc}

# Context
This was a homework assignment for the class _AE6766 Combustion_ at Georgia Tech, but I wanted to hone my visualization skills using Plotly so I put a little extra effort into it. 

# Task

For a mixture of propane and air at varying [equivalence ratios](#equivalence-ratio) and starting at STP, determine the [adiabatic combustion temperature](#adiabatic-combustion-temperature) and [equilibrium gas composition](#equilibrium-gas-composition) (for these specific species) at constant pressure.

# Results

[Figure 1](#figure-1-equilibrium-composition-mole-fraction-animation) contains an animation showing how the equilibrium composition changes as a function of the equivalence ratio. At a phi of 0 there is no fuel, so the mole fraction of oxygen is 21%, as the assumed composition of air was 21% O2, 79% N2. Then, from phi of 0 to 0.7 O2 begins to get converted to CO2 and H20 as the products of propane combustion. At a phi of 0.8 we begin to see additional species such as OH which form as intermediaries to the combustion reaction and from the dissociation of water as the adiabatic temperature begins to rise. In fact, the changing compositions viewed here are a result of both the changing intial composition of the gas mixture (more propane as phi increases) and because the adiabatic temperature changes with phi, as visible in [Figure 2](#figure-2-equilibrium-combustion). As phi climbs above 1, CO becomes a major component of the equilibrium mixture as there is not enough oxygen to bring the combustion reaction to completion. 

### Figure 1: Equilibrium Composition Mole Fraction Animation
[Standalone Figure](https://corradomazzarelli.com/assets/blog_posts/bp.equilibrium_cantera/HP_mole_fraction_animation.html)
{% include bp.equilibrium_cantera/HP_mole_fraction_animation.html %}

In [Figure 2](#figure-2-equilibrium-combustion) the adiabatic combustion temperature, the [specific heat capacity Cp](#specific-heat-capacity), and the equilibrium compostion can be viewed in a line plot. The portion interest in this plot is the adiabatic combustion temperature. It is clear from the plot that the temperature peaks when phi is equal to 1, since that is where the gas mixture is [stoichimetric](#stoichimetric-ratio). 

### Figure 2: Equilibrium Combustion 
[Standalone Figure](https://corradomazzarelli.com/assets/blog_posts/bp.equilibrium_cantera/HP.html)
{% include bp.equilibrium_cantera/HP.html %}

## Shortfalls of the Analysis

This assignment neglected NOx production in the desired species. NOx, or nitrogen oxides, play a significant role in combustion processes and their environmental impact. These compounds, such as nitrogen dioxide (NO2) and nitric oxide (NO), are formed during high-temperature combustion reactions, particularly in engines and power plants. NOx emissions contribute to air pollution and have adverse effects on human health, including respiratory issues and the formation of ground-level ozone. Additionally, NOx is a key precursor to acid rain, which can harm ecosystems and aquatic environments. Ignoring NOx production in articles on combustion overlooks a crucial aspect of the process and its environmental consequences, emphasizing the importance of addressing and mitigating NOx emissions for sustainable and cleaner combustion technologies.

The production of nitrogen oxides (NOx) in combustion processes is a complex series of chemical reactions involving nitrogen and oxygen present in the air. The primary mechanism leading to NOx formation is known as thermal NOx formation. At high temperatures, typically above 1,400 degrees Celsius (2,552 degrees Fahrenheit), nitrogen and oxygen molecules in the air react to form nitrogen oxides. Control and reduction of NOx emissions often involve optimizing combustion conditions, employing exhaust gas recirculation, and using selective catalytic reduction (SCR) technologies to convert NOx into less harmful nitrogen and water vapor. Understanding the scientific basis of NOx formation is crucial for developing strategies to mitigate its environmental impact and promote cleaner combustion technologies.

# Concepts

## Equilibrium Gas Composition

In the realm of thermodynamics, equilibrium gas composition refers to the distribution of chemical species in a gas mixture when the system has reached thermodynamic equilibrium. At this state, there is no net change in the concentrations of various species, and the system's properties remain constant over time. The equilibrium gas composition is determined by factors such as temperature, pressure, and the initial composition of the gas mixture.

Understanding equilibrium gas composition is crucial in various fields, including chemistry, chemical engineering, and environmental science. It helps predict the distribution of different molecules in a gas phase under specific conditions, allowing scientists and engineers to optimize processes and design systems with greater efficiency.

## Equivalence Ratio

The equivalence ratio is a parameter used in combustion engineering to describe the ratio of the actual fuel-to-oxidizer mixture to the stoichiometric fuel-to-oxidizer ratio required for complete combustion. It is a key factor in determining the efficiency and characteristics of combustion processes. The equivalence ratio influences whether a mixture is fuel-rich, stoichiometric, or fuel-lean.

An equivalence ratio equal to 1 indicates a stoichiometric mixture, where all the fuel and oxidizer react completely. Values greater than 1 signify a fuel-rich mixture, while values less than 1 indicate a fuel-lean mixture. Engineers use the equivalence ratio to optimize combustion processes, ensuring efficient energy release and minimizing the production of pollutants.

## Adiabatic Combustion Temperature

The adiabatic combustion temperature refers to the theoretical temperature reached during combustion when the process is adiabatic, meaning there is no heat exchange with the surroundings. When pressure is held constant during combustion, it is known as constant-pressure or isobaric combustion.

## Specific Heat Capacity

Cp represents the specific heat capacity at constant pressure. Specific heat capacity is a measure of the amount of heat energy required to raise the temperature of a unit mass of a substance by 1 degree Celsius (or 1 Kelvin).

## Stoichimetric Ratio

Stoichiometric refers to the precise balance of reactants in a chemical reaction according to the mole ratios indicated by the balanced chemical equation. In a stoichiometrically balanced reaction, the number of moles of each reactant and product is in the exact proportion specified by the coefficients in the balanced equation.

## Cantera

Cantera is an open-source software suite used for solving problems that involve chemically reacting systems. It is particularly powerful in the fields of chemical kinetics, thermodynamics, and transport processes. Cantera provides a set of tools and libraries for simulating chemical reactions, equilibrium calculations, and the behavior of reacting flows.

Engineers and researchers use Cantera to model and simulate complex chemical processes, combustion reactions, and heat transfer phenomena. The software allows users to define chemical mechanisms, simulate reactions under different conditions, and analyze the thermodynamic properties of reacting systems. Cantera plays a significant role in advancing research and development in areas such as combustion engines, environmental science, and materials science.


# Python Libraries

## Cantera
"[Cantera](https://cantera.org/) is an open-source suite of tools for problems involving chemical kinetics, thermodynamics, and transport processes."

## Numpy
[Numpy](https://numpy.org/) is a powerhouse in scientific Python analysis, and needs no introduction.

## Plotly
[Plotly](https://plotly.com/python/) is a widely used plotting library which enables easy interactive plots which can be saved as interactive. They are the plots you'll see embedded here.

# Code

## Environment.yml

[Link to environment.yml](https://corradomazzarelli.com/assets/blog_posts/bp.equilibrium_cantera/environment.yml)


## Source Code 

{% highlight python linenos %}
# -*- coding: utf-8 -*-
"""
Created on Sat Jan 20 12:37:29 2024

@author: mazzac3
"""

import numpy as np
import pandas as pd
import cantera as ct
from tqdm import tqdm
import plotly.express as px
import plotly.graph_objects as go
from plotly.subplots import make_subplots


# ----------------------------------------------------------------------------------------------------------------------
# Define Inputs
# ----------------------------------------------------------------------------------------------------------------------


phi_vals = np.around(np.linspace(0, 2, 21), decimals=2)
p_0 = 101325  # Pa
T_0 = 298  # K
equilibration_modes = {
    "HP": "Constant Enthalpy and Pressure",
    # "TP": "Constant Temperature and Pressure",
    # "TV": "Constant Temperature and Volume",
    # "SP": "Constant Entropy and Pressure",
    # "SV": "Constant Entropy and Volume",
    "UV": "Constant Internal Energy and Volume"
}



air = "O2:0.21,N2:0.79"  # Define the oxidizer composition
fuel = "C3H8:1"
species_list = ['CO2', 'CO', 'H2O', 'H2', 'O2', 'OH', 'O', 'H']

# ----------------------------------------------------------------------------------------------------------------------
#%% Generate Results
# ----------------------------------------------------------------------------------------------------------------------


gas = ct.Solution('gri30.yaml')  # Create the gas mixture

# Initialize a dictionary to hold the results
raw_results = {}

#  https://cantera.org/examples/python/thermo/equivalenceRatio.py.html
for equilibration_mode in equilibration_modes:
    raw_results[equilibration_mode] = ans = {}  # Create a dict to store the results
    ans["Tad"] = np.zeros_like(phi_vals)  # Put a location to store Tad
    ans["Cp"] = np.zeros_like(phi_vals)  # Put a location to store Cp
    ans["Mole Fractions"] = np.zeros((len(phi_vals), len(species_list)))
    
    for i, phi in enumerate(tqdm(phi_vals, desc=f"Processing Constant {equilibration_mode}")):
        
        # Mix the fuel and air according to phi
        gas.set_equivalence_ratio(phi=phi, fuel=fuel, oxidizer=air)
        
        # Set the starting temperature and pressure
        gas.TP = T_0, p_0
        
        # Equilibrate the gas at constant XX properties
        gas.equilibrate(equilibration_mode)
        
        # grab the desired outputs
        ans["Tad"][i] = gas.T
        ans["Cp"][i] = gas.cp
        ans["Mole Fractions"][i] = gas[species_list].X
        
    

# ----------------------------------------------------------------------------------------------------------------------
#%% Format Results
# ----------------------------------------------------------------------------------------------------------------------

result_dataframes = {} # store
for equilibration_mode in raw_results:
    
    # This could be refactored but it's not worth the effort
    
    # Put the mole fractions into dataframes
    raw_results[equilibration_mode]["Mole Fractions"] = pd.DataFrame(
        raw_results[equilibration_mode]["Mole Fractions"],
        columns=species_list,
        index=phi_vals
    )
    
    
    # Put the temperatures into dataframes
    raw_results[equilibration_mode]["Tad"] = pd.DataFrame(
        raw_results[equilibration_mode]["Tad"],
        columns=["Tad"],
        index=phi_vals
    )
    
    # Put the Cp into dataframes
    raw_results[equilibration_mode]["Cp"] = pd.DataFrame(
        raw_results[equilibration_mode]["Cp"],
        columns=["Cp"],
        index=phi_vals
    )
    
    # Combine the dataframes
    result_dataframes[equilibration_mode] = pd.concat([
        raw_results[equilibration_mode]["Mole Fractions"],
        raw_results[equilibration_mode]["Tad"],
        raw_results[equilibration_mode]["Cp"],],
        axis=1
    )
    
    

# ----------------------------------------------------------------------------------------------------------------------
#%% Plot Results
# ----------------------------------------------------------------------------------------------------------------------

# Create plots for the homework
for equilibration_mode, df in result_dataframes.items():
    
    # Create subplots
    fig = make_subplots(rows=3, cols=1, subplot_titles=['Tad', "Cp" , 'Species Mole Fractions'], shared_xaxes=True)
    
    # Add the species
    for col in df.columns:
        row = 1 if col =="Tad" else 2 if col == "Cp" else 3
        
        fig.add_trace(go.Scatter(x=phi_vals, y=df[col], mode='lines', name=col), row=row, col=1)

   # Update title and stuff
    fig.update_layout(
        xaxis3=dict(title='Phi'),
        yaxis=dict(title='Temperature (K)'),
        yaxis2=dict(title='Cp (J/kg.K)'),
        yaxis3=dict(title='Mole Fraction'),
        title=f'{equilibration_modes[equilibration_mode]} -- Propane Equilibrium Combustion',
        hovermode='x unified'  # Set xunified hovermode
    )

    fig.show(renderer="browser")
    fig.write_html(f"../plots/{equilibration_mode}.html")

# ----------------------------------------------------------------------------------------------------------------------
#%% Create Mole Fraction Animation 
# ----------------------------------------------------------------------------------------------------------------------

for equilibration_mode, df in result_dataframes.items():
    
    # Reformat the DF for the animation 
    reformatted_df = pd.concat(
        [
            pd.DataFrame({
                "Phi": phi_vals,
                "Species": [species] * len(phi_vals),
                "Mole Fraction": df[species].tolist(),
            })
        for species in species_list]
    ).reset_index(drop=True)
    
    
    # Create the animation
    fig = px.bar(
        reformatted_df,
        x="Species", 
        y="Mole Fraction",
        color="Species", 
        animation_frame="Phi", 
        range_y=[0, 0.25],
        title=f'{equilibration_modes[equilibration_mode]} -- Propane Equilibrium Combustion Composition'
        )
    
    fig.show(renderer="browser")
    fig.write_html(f"../plots/{equilibration_mode}_mole_fraction_animation.html")

{% endhighlight %}
---
layout: post
title: Making Sense of Chemical Manufacturers Corporate Goals on Reducing Carbon Footprint
subtitle: Rethinking the role of process flow analysis in identifying carbon reduction opportunities in chemical manufacturing
thumbnail-img: /assets/img/2021-12-28-thumb.jpg
tags: [industry]
comments: true
---

The chemical manufacturing industry is a significant contributor to global greenhouse gas emissions, although the estimates of its share of the total carbon footprint vary depending on the source of data and the specific sector or region considered. Thus, according to the Global Change Data Lab, the chemical industry accounted for about 6% of global CO2 emissions in 2020, while 60% of it comprise energy related enissions.<sup>1,2</sup>

**Two main instruments** are available for chemical manufacturers to identify and implement measures to reduce their carbon footprint: Life Cycle Assessment (LCA) and Process Flow Analysis (PFA). Both tools have been developed and constantly improved in response to the growing concern over the environmental impacts of human activities, and have been adapted to different sectors and industries, providing a more specialized approach, such as carbon footprinting, water footprinting, and even social life cycle assessment. The origins of **LCA can be traced back to the 1970s**, when the concept of "ecological footprint" was first introduced. In the early days, LCA focused primarily on the environmental impacts of specific goods, such as a car or a refrigerator. During the 1980s and 1990s, LCA evolved to include a more comprehensive assessment of the **environmental impacts of products**, considering the entire life cycle of the product, from the extraction of raw materials to the disposal of the product at the end of its life.

PFA, on the other hand, is a more recent tool that has emerged because of the increased focus on the environmental impacts of industrial processes. **PFA is a specialized form of LCA** that is used to evaluate the **environmental impacts of specific industrial processes**, rather than individual products. PFA aims to provide a detailed analysis of the energy consumption, material and energy inputs and outputs, and emissions associated with each process step, therefore allowing companies to identify specific areas where emissions can be reduced.

**The overall concept of carbon footprinting has evolved over time**. The first carbon footprint calculations were relatively simple and focused primarily on direct emissions, such as emissions from combustion of fossil fuels. These calculations were typically based on emissions factors, which are estimates of the emissions associated with a specific activity or product.

**As the understanding of the complexities of carbon footprinting has grown, so has the sophistication of the methods used to calculate it**. The carbon footprint calculation has evolved to include not only direct emissions but also indirect emissions, such as those associated with the production of electricity used in a process, and the transportation of materials.  In 1998, the **Greenhouse Gas (GHG) Protocol** was first developed by the World Resources Institute (WRI) and the World Business Council for Sustainable Development (WBCSD) with the goal of providing a consistent and transparent framework, a standard nowadays, for measuring and reporting greenhouse gas emissions.<sup>3</sup>

The GHG Protocol has undergone several revisions since its first release.  Initially, it included two scopes: Scope 1 which includes direct emissions from sources that are owned or controlled by the company, and Scope 2 which includes indirect emissions from the generation of purchased electricity, heat, or steam. In 2001, the GHG Protocol expanded its scope to include the entire value chain of a company, including its suppliers and customers, with the introduction of Scope 3, the Supply Chain and Value Chain Accounting and Reporting Standard. In 2004, the GHG Protocol introduced the Product Life Cycle Accounting and Reporting Standard.

**The most recent developments in carbon footprinting have been the incorporation of Life Cycle Assessment (LCA) and Process Flow Analysis (PFA) in the calculation and development of LCA- and PFA-based software**. These software tools are designed to enable companies to conduct a thorough analysis of their manufacturing processes, providing a comprehensive overview of the energy consumption, material inputs and outputs, and emissions associated with each process step. Breaking down the process into smaller units can help companies identify specific areas where emissions can be reduced. There is one tricky question though: **what kind of data is fed into the software?** Let’s dig into it.

The information on each process step can come from one of the two possible sources: measurement or estimates. Consider energy consumption as an example:
1. **Measurements**: The energy consumption of each process step can be measured directly using energy meters or other monitoring equipment. This information can be used to provide accurate and detailed data on the energy consumption of each process step.
2. **Estimates**: 
    - Engineering estimates can be performed by engineers who make estimates of the energy consumption of each process step based on their knowledge of the process and the equipment used.
    - Process simulation software<sup>4</sup> can be used to support this effort and estimate the energy consumption of each process step. Thus, some process simulation software, commonly used in the chemical industry for analysis of process parameters and optimization the process conditions, also provide carbon footprint calculations.
    - Benchmark data on energy consumption for similar processes or equipment can be used as a reference to estimate the energy consumption of a specific process.

**Historically, carbon footprint calculation software was able to employ only estimates**. Thus, the calculations used by the software are typically structured in accordance with the LCA methodology, when the estimates are conducted within the step called **inventory analysis**<sup>5</sup>. Inventory analysis includes the collection of data on inputs and outputs of the process and the emissions generated by the process:

1. Inputs to the product or process: the type and the volume of raw materials used, the energy and water consumed, and the emissions generated during the production of the raw materials.
2. Outputs of the product or process: the type and amount of product produced, the emissions generated during the manufacturing process, and the emissions associated with the use and disposal of the product.
3. Emissions data associated with each stage of the product's life cycle: emissions associated with the extraction and transport of raw materials, the emissions generated during the manufacturing process, and the emissions associated with the use and disposal of the product.

The level of resolution of the inventory analysis depends on the specific software: it ranges from a broad overview of the process to a detailed analysis of individual process steps. PFA-based software is supposed to **provide a high level of resolution of the inventory analysis by breaking down the process into smaller units or sub-processes based on its Process Flow Diagram** (PFD)<sup>6</sup>. How does it actually work?
1. A PFD can be created using specialized process flow diagram software and imported into the PFA software. Some PFA software also allows the PFD to be created directly within the software.
2. Once the PFD is established within the PFA software, data such as the energy consumption, material and energy inputs and outputs, and emissions associated with each process step can be associated with the corresponding process step on the PFD. Here comes the moment of truth: do we feed the PFA software with estimates (simulations) or with real monitoring data?

When it comes to the task of implementing ambitious corporate goals on a practical level, it is crucial for companies to establish accurate and near real-time measurement of energy consumption and emissions to extract actionable insights for reducing their carbon footprint. The increasing demand for and advancements in technology have sparked further development of carbon footprint calculation software that **integrates automated energy metering solutions**, allowing for **accurate estimates of energy consumption for each process step**. Of course, utilizing such software necessitates having automated energy metering solutions already in place, which can be costly and might require a certain level of expertise. 

This next generation of carbon footprint calculation software tools<sup>7</sup>, employes data from energy meters or other monitoring equipment to provide real-time or near real-time data on both consumption of materials and energy and emissions at each process step.<sup>8</sup> **But even more exciting developments are to come.** Let’s face it: Scope 1 and Scope 2 are someone else’s scope 3 emissions, while downstream corporate leaders often can excercise their critical position within the value chain to drive the change<sup>9</sup>. With the introduction of the Border Carbon Adjustment (BCA) mechanism<sup>10</sup>, **upstream chemical manufacturers will be required to report on the carbon content of the exported goods**, either to the regulatory body or to the importing party. Guess what level of details would be required in carbon footprint measurement to effectively manage and align with the demands of customers?

Copyright © 2021 Zheniya Mogilevski

<sup>1</sup> See: [Our World in Data](https://ourworldindata.org/emissions-by-sector).

<sup>2</sup> It is worth noting that these numbers might exclude or include some aspects of the entire carbon footprint of the chemical industry, as it also includes emissions from the production of feedstocks, transportation of raw materials and products, and the use of chemical products in other sectors.

<sup>3</sup> See: [GHG Protocol](https://ghgprotocol.org/about-wri-wbcsd).

<p><sup>4</sup> See: Aspen HYSYS, Aspen Plus, Pro-II and UniSim.</p>
<p><sup>5</sup> See: SimaPro, GaBi, OpenLCA, Ecoinvent.</p>
<p><sup>6</sup> PFDs are used to represent the process graphically, and they provide an overview of the process, the equipment used, and the flow of materials and energy through the process. The data used for estimating by process simulation depends on the specific software and process being simulated, but it typically includes: PFDs, process conditions such as temperature, pressure, and flow rates, data on the equipment used in the process, such as heat exchangers, pumps, and reactors including information on the size, design, and efficiency of the equipment, data on the properties of the materials used in the process, such as density, heat capacity, and thermal conductivity, data on the thermodynamic properties of the materials used in the process, such as heat of reaction, enthalpy, and entropy, data on the kinetic properties of the materials used in the process, such as reaction rates, data on the emissions generated by the process, such as carbon dioxide, methane, nitrous oxide and others.</p>
<p><sup>7</sup> One example of such software is myCarbonCure by CarbonCure Technologies.</p>
<p><sup>8</sup> Additionally, some providers of automated energy metering solutions, such as Siemens, ABB, and Schneider Electric developed, provide software and services for energy management and optimization, which can be used to monitor and reduce energy consumption, and thus also the associated carbon footprint.</p>

<sup>9</sup> See: [TfS Initiative](https://www.tfs-initiative.com/what-we-do) founded by BASF, Bayer, Evonik, Henkel, Lanxess, and Solvay.
<sup>10</sup> See: [CBA mechanism](https://taxation-customs.ec.europa.eu/green-taxation-0/carbon-border-adjustment-mechanism_en).

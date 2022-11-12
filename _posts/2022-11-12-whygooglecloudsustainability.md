---
layout: post
title: Why Google Cloud?
subtitle: "Part 2: Sustainability"
#cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/Green-Google-Logo.jpg
share-img: /assets/img/Green-Google-Logo.jpg
readtime: true
share-title: Why Google Cloud?
share-description: Sustainability- In this blog I list 9 ways to reduce your carbon emissions when migrating to Google Cloud and highlight the success Google has had to date contributing towards achieving net-zero. Google has been a leader in sustainability for a long time. They're striving for net-zero carbon emissions, and creating technologies to help other organisations reduce their carbon footprint too.
share-img: /assets/img/Green-Google-Logo.jpg
tags: [sustainability, carbon emmissions, energy, cfe%]
---
Hello, welcome to my blog series on ‘Why Google Cloud?’ This is my second blog in the series, focusing on sustainability. If you have missed the first blog on Security it is available to read here [Why Google Cloud Part 1: Security](https://www.cloudbabble.co.uk/2022-11-03-whygooglecloudsecurity).

This decade is critical for setting the world on a path to a sustainable future. In order to meet the objectives of the 2015 Paris Agreement and keep global warming within 1.5 degrees Celsius of pre-industrial levels, the global economy needs to halve emissions by 2030 and become net-zero by 2050. A new report from UN Climate Change shows countries are bending the curve of global greenhouse gas emissions downward but underlines that these efforts remain insufficient to limit global temperature rise to 1.5 degrees Celsius by the end of the century.

According to the report, the combined climate pledges of 193 Parties under the Paris Agreement could put the world on track for around 2.5 degrees Celsius of warming by the end of the century.

In this blog I highlight the success Google has had to date contributing towards achieving net-zero, and features within Google Cloud that can help organisations reduce their carbon footprint as part of a migration to public cloud. Google has been a leader in sustainability for a long time. They're striving for net-zero carbon emissions, and creating technologies to help others reduce their carbon footprint too.

## Carbon Neutral Since 2007
Google were the first major company to become carbon neutral in 2007. Organisations that are carbon neutral compensate their carbon emisssions via carbon offsetting projects i.e. they've taken steps to remove the equivalent amount of CO2 to what's emitted through activities across their supply chains via methods such as 'carbon sinks' that absorb CO2.

## Matched Energy Usage with Renewable Energy 2017
10 years later in 2017, Google became the first major company to match their energy use with 100% renewable energy, and have continued to do so for 5 consecutive years.

## $5.75 Billion Sustainability Bonds 2020
In 2020 Google issued $5.75 billion in sustainability bonds- the largest sustainability issuance by any company in history. Sustainability, or green bonds are issued where proceeds are used to finance or re-finance a combintion of green and social projects. 

## Carbon Neutral Legacy Footprint 2020
In 2020 Google also compensated their legacy carbon footprint, making Google the first major company to be carbon neutral for its entire operating history! All carbon emisisions from Google's founding in 1998, up until 2007 when they achieved carbon neutrality, have been eliminated. Google's lifetime net carbon footprint is now zero.

## 2030 Targets
Google have also set ambitious targets to achieve by 2030 including:

- To run on carbon free energy 24/7, across all data centers and campuses worldwide.
- Achieve net-zero emissions across all their operations and value chaing.
- Enable 5 gigawatts of new carbon-free energy through investments in Google's key manufacturing regions.
- Help more than 500 cities and local governments reduce an aggregate of 1 gigaton of carbon emissions annually.

![Google's Energy Journey](/assets/img/Googles-energy-journey.jpg "Google's Energy Journey")

***Google's Energy Journey*** 
[Image Source: Google](https://sustainability.google/progress/energy/)

## Efficient Data Centers
  - On average, Google Datacenters are 2x as energy efficient as a typical enterprise data center.
  - Compared to 5 years ago, Google now generates around 6 times as much computing power with the same amount of electrical power.
  - In 2020 the average annual PUE for Google was 1.10 compared with industry average of 1.59 meaning that Google data centers use about six times less overhead energy.
  - Through applying Machine Learning, Google have been able to reduce the cooling energy required for their data centers by 40%.
  
### Green House Gas (GHG)
  - Zero operational GHG emissions: Whether someone is using Google at home or as part of an organization running Google Cloud or Google Workspace, all products in Google Cloud are carbon neutral, meaning that the operational GHG emissions associated with running workloads on Google's infrastructure have been reduced through procurement of renewable energy and any residual emissions have been compensated for with high-quality carbon credits.

### Waste
  - 78% of waste from global data center operations is diverted away from landfill.
  - 23% of components used for server upgrades were refurbished inventory.
  - 8.2 million components were wiped clean and resold into the secondary market for reuse by other organisations in 2020.

# How Can Google Cloud Help Improve My Carbon Footprint
Organisations migrating to Google Cloud benefit from all of the above when it comes to measuring carbon emissions. As a result, simply migrating applicaitons to Google Cloud can result in significant reductions in the workloads carbon emissions. However, there are various actions organisations can take during migration to Google Cloud that can result in further lowering the carbon footprint of workloads.

Google Cloud publishes Carbon Free Energy percentage (CFE%) metrics for all regions. This metric shows how often a region is supplied with carbon free energy on an hourly basis. This values are published:

- [On Google Docs](https://cloud.google.com/sustainability/region-carbon)
- [On Github](https://github.com/GoogleCloudPlatform/region-carbon-info)
- [On BigQuery as a public dataset](https://console.cloud.google.com/marketplace/product/bigquery-public-datasets/regional-cfe?_ga=2.120231425.845394051.1668196466-99251301.1630672239)

![Google Cloud Carbon Free Energy Percentage Global Map](/assets/img/Carbon-free-energy-map.jpg "Carbon Free Energy Global Map")

***Google Cloud Carbon Free Energy Percentage (CFE%) Global Map*** 
[Image Source: Google](https://sustainability.google/progress/energy/)

Alternatively, within the Google Cloud console, a green leaf icon and 'low CO2' next to a region indicates a region with a CFE% of at leeast 75% (8 regions currently have CFE% greater than 75%). Selecting a Google CLoud Region with a higher CFE% rating can help further reduce carbon emissions than deploying infrastructure in a region with a lower CFE%.

![Google Cloud Carbon Free Energy Percentage CFE%](/assets/img/Cloud_Run_region_selector.max-700x700.jpg "Carbon Free Energy Green Leaf")

***Google Cloud Carbon Free Energy Percentage (CFE%)*** 
[Image Source: Google](https://cloud.google.com/blog/topics/sustainability/pick-the-google-cloud-region-with-the-lowest-co2)

## 9 Recommendedations To Minimise Carbon Emissions 

Below are nine approaches I recommend as part of a migration/deployment to Google Cloud to minimise carbon emissions associated with your workloads.

1. Deploy application workloads to regions with higher CFE ratings to reduce their carbon footprint.
2. Run batch jobs in regions with the highest CFE ratings to reduce their carbon footprint. Bathc jobs have the benefit of running on a schedule and can therefore be planned to run in the lowest carbon emitting regions, maximising carbon emission savings.
3. Define organisation policies to restrict users from deploying infrastructure to regions with a low CFE% rating. This ensures all workloads are deployed to the lowest carbon emitting regions you define, preventing users who may not have sustainability at forefront of mind, accidnetly deploying to a region with a lower CFE% value. This also mitigates against and 'test' or 'temporary' infrastructure deployed to default regions for short periods of time.
4. When modernising applications, aim for serverless products that scale your workload up and down with demand. 
5. Design architecture that can scale to zero instead of having idle instances running 24/7 to maximise carbon emission savings!
6. Even for simple rehost migrations, put time in to right size VM instances before deploying on Google Cloud. Optimising the VM size to consume no more resource than it requires reduces the overall energy demand and associated carbon emissions.
7. Regularly review right sizing recommendations from Google Cloud to ensure you are running on the optimal hardware configuration throughout the lifecycle of the workload. As applicaitons go through different stages of their lifecycle, peak changes in usage may change over time meaning further optimisations can be achieved by regularly reviewing.
8. Regularly review and decommission unused projects and resources. Idle resources are consuming power, contributing to carbon emissions and incurring unecessary charges!
9. Review application code to identify any opportunities to improve it's efficiency. Designing efficient application code reduces power consumption, and the workloads carbon footprint.

It may not always be practical to run all workloads in the most CFE% regions due to data residency constraints, application latency and performance requirements, or redundancy requirements. However, by adopting policies that deploy to the higehst rated CFE% regions first, those workloads that can be deployed to these regions will benefit from lower carbon emissions. Whilst it's true individually the above will have a very little impact in achieving the Paris Agreement objectives, collectively if we all make these small changes that are recommended in our day to day lives, together then we will start to see us move nearer towards that 1.5 degrees Celcius target.

## Idle Resources
In 2021, Google analysed the aggregate data from all customers across Google Cloud to identify idle projects that could be cleaned up or removed. This analysis found over 600,000 gross kgCO2e was consumed by idle projects. Cleaning up these idle projects would have had the same impact as planting almost 10,000 trees!

To help organisations tidy up unused projects, Google's AIOps has created Active Assist which uses data, intelligence and machine learning to identify unused projects and alert organisations to help achieve sustainability targets and reduce carbon footprints of the unused workloads. This comes with the added bonus of reducing unnecssary costs!

## Investing In Innovators To Tackle Climate Change

Beyond Google's own tools and programs, Google also invests in promising initiatives that aim to create scalable, high-impact climate solutions. Google.org, Google's charitable arm, is providing catalytic funding to innovative projects around the world including:

- The Impact Challenge on Climate Innovation, a $30 million fund to support breakthrough projects that use data and technology to accelerate climate action. Selected organizations will receive up to $5 million in funding to scale their activities, along with access to Google’s technical expertise and products to help hem maximize their impact.
- AI for the Global Goals, a $25 million fund to support the development of new AI-driven approaches that accelerate progress on the UN Sustainable Development Goals (SDGs).
- A $10 million grant to ICLEI-Local Governments for Sustainability to fund ten nonprofit-led projects that advance sustainable cities.
- The Environmental Justice Data Fund, a $9 million fund managed by the Windward Fund that provides flexible funding to U.S.-based environmental justice organizations to collect data and build data analysis capacity that will enable communities to apply for infrastructure funding from the U.S. federal government.

## Helping Eveyone Make Sustainable Choices
In addition to reducing their own carbon emissions, investing in innovation to help tackle climate change, and helping other organisations reduce their carbon footprint, Google has also made various solutions available to everyone, to help the public make their own informed sustainability choices through:

- Supporting more sustainable transport: Google maps now provides eco friendly routes, enabling users to get to their destinations quickly whilst minimising fuel or battery consumption by leveraging Google's AI tools and insights. This is already estimated to have remove over half a million metric tonnes of carbon emmissions (the equivalent of taking 100,000 fuel based cars off the road!
- Enabling More Sustainable Travel Choices: Users searching for flights now see carbon emissions estimates for nearly every flight, right next to price and duration. Loweremissions flights are labeled with a green badge, and users can sort results by carbon impact.
- Hotels: When our users search for travel accommodations, they now see information about hotels’ sustainability efforts. 
- Nest thermostats: Google's Nest thermostats have proven energy savings of 10-12% for heating peoples homes. The collective impact of these savings is significant: as of October 2022, Nest thermostats have helped customers cumulatively save more than 105 billion kWh of energy—more than double Portugal's electricity consumption in 2020. 

# Conclusion
Google has an impressive sustainability record, they have a lifetime net-carbon footprint of zero, continue to invest in innovation to tackle climate change globally and help organisations reduce their carbon emissions by operating the cleanest global cloud in the industry! With Carbon Free Energy Percentage metrics and Active Assist Unattended Project Detector, organisations can reduce their application workloads carbon footprint by provisioning resources in low carbon energy regions, and decommissioning unused resources. It's these features and sustainability credentials that makes Sustainability one of my reasons 'Why Google Cloud.'

Thanks for taking the time to read this blog. Please feel free to share, [subscribe](https://www.cloudbabble.co.uk/subscribe) to be alerted to future posts, follow me on [LinkedIn](https://linkedin.com/in/jamiethompson85), and react/comment below! 

Do reach out if you would like me to cover any particular areas of Google Cloud products, concepts or certifications in future posts.

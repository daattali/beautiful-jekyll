---
layout: post
title: When are you most likely to be killed by a bear? (Makeover Monday 2019/W21)
tags: [data science, makeover monday]
---

This weeks [Makeover Monday challenge](https://data.world/makeovermonday/2019w21) used fatal bear attack data recorded over the past century.

The vis was from a [Vox article](https://www.vox.com/2016/10/6/13170344/bear-attacks-national-state-parks) about bear attacks. The original vis looked like this:

![](https://media.data.world/tNjcdXZAQZuepWQVOiHs_Screenshot%202019-05-19%20at%2011.02.36%20am.png)

The dashboard I created can be found on [Tableau Public](https://public.tableau.com/views/WhenareyoumostlikelytobekilledbyabearMakeoverMonday2019W21/BearDeaths?:embed=y&:display_count=yes&:origin=viz_share_link).

![](https://pbs.twimg.com/media/D8mmlSZU8AYdJvc?format=jpg&name=4096x4096)

The original data was for the most part clean, but required a few transformations. I used R to clean the location data for visualizing in Tableau.

~~~~
library(dplyr)
library(tidyr)
setwd("~/Documents/Projects/Makeover Monday/2019_W21_Bears")

# download the data
if (!file.exists("bear_fatality.csv")){
  print("downloading dataframe...")
  url <- "https://query.data.world/s/2ihpzhbt36iagn3vudp3pnkrvkgd7q"
  download.file(url = url, destfile = "north_america_bear_killings.csv")
} else {print("Data frame already downloaded")}

# read data
bear <- read.csv("north_america_bear_killings.csv", header=TRUE, stringsAsFactors=FALSE)

# add in location details
bear$State <- stringr::str_split_fixed(bear$Location, ",", 2)[,2]
bear$City <- stringr::str_split_fixed(bear$Location, ",", 2)[,1]

# remove "near" from city column
bear$City <- gsub(pattern = "near *", x = bear$City, replacement = "")

# trim the white space
bear <- bear %>%
  mutate(State = stringr::str_trim(State, side = "both"),
         City = stringr::str_trim(City, side = "both"))

# fix known errors
bear <- bear %>%
  mutate(State = case_when(
    Location == "New York City" ~ "New York",
    Location == "Yellowstone National Park" ~ "Wyoming",
    TRUE ~ State
  ))

# add country
bear <- bear %>%
  mutate(Country = case_when(
    State == "British Columbia" ~ "Canada",
    State == "Alberta" ~ "Canada",
    State == "Saskatchewan" ~ "Canada",
    State == "Manitoba" ~ "Canada",
    State == "Ontario" ~ "Canada",
    State == "Quebec" ~ "Canada",
    State == "New Brunswick" ~ "Canada",
    State == "Nova Scotia" ~ "Canada",
    State == "Prince Edward Island" ~ "Canada",
    State == "Newfoundland and Labrador" ~ "Canada",
    State == "Northwest Territories" ~ "Canada",
    State == "Yukon" ~ "Canada",
    State == "Nunavut" ~ "Canada",
    TRUE ~ "United States"
  ))

# export data
export_data <- TRUE
if (export_data){
  write.csv(bear,"north_america_bear_killings_CLEAN.csv")
}
~~~~
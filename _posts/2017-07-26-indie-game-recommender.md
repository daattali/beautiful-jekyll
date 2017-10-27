---
layout: post
title: Indie Game Recommender
subtitle: Galvanize Capstone Project
image: /img/indie_game_average_playtimes.png
tags: [NMF, ALS, Spark, Data Products, Recommender, Galvanize]
---

![alt text](pixelatedbrian.github.io/img/indie_game_average_playtimes.png)

Scraped 10M user playtimes of games tagged as indie from Steam.com. Stored preprocessed and processed data in MongoDB. Performed Log10 transformation of playtimes and used Non-Negative Matrix Factorization (Spark ALS implementation) to make predictions on what the estimated playtimes of games would be for a user. Then recommended the top 10 playtime of games to the users. 

Did several rounds of iteration to improve the results as the first iteration of the project simply recommended games with the highest average playtimes. The Log10 transformation helped a lot with that particular issue. A system of weightings was also developed to penalize different types of games. In particular games under development had very high average playtimes but very few total users in the sample. (Which makes sense as the game is not yet available to the public yet.) The playtimes of these games would be penalized by the weighting system which reduced those kinds of issues.

![alt text](pixelatedbrian.github.io/img/rmse_vs_rank.png)

Reference-style: 
A train/test split of the data was performed for cross validation. The results were quite promising as many games in the holdout set would appear as recommended games for the user. There wasn't enough time during capstone to create a data product website that was public facing but that is still a desired outcome for a later date.

Many more details [here](https://github.com/pixelatedbrian/Indie-Game-Recommender/blob/master/README.md)

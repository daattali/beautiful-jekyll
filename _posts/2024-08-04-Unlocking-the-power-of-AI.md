---
layout: post
title: Unlocking the Power of AI - How to Build a Simple AI Chatbot
subtitle: A Hands-On Guide to Creating Your First AI Chatbot
date: 2024-08-04 18:40:00 +0530
categories: jekyll update
gh-badge: [star, fork, follow]
tags: [ai, python, chatbot]
comments: true
author: Harish Sarma
---

Below, you’ll find a step-by-step guide to building a simple AI chatbot using Python. This guide is designed to help you get started with AI and create a functional chatbot that you can customize and expand upon.

**Here’s What You’ll Learn**:

Click to Expand: Follow the instructions to build your chatbot and learn how AI can be applied in real-world scenarios.

**Step-by-Step Instructions**:

<details>
    <summary style="font-weight: 800;">Step 1: Set Up Your Environment <img alt="Setup" width="20" src="https://img.icons8.com/material-outlined/24/000000/setup.png"> </summary>

<h3><ins>Overview</ins></h3>
<p>First, you need to install the necessary Python library to get started with building your chatbot. This setup will ensure that you have the tools required for the project.</p>

<h3><ins>How to Install</ins></h3>
<ul>
    <li>Open your terminal or command prompt.</li>
    <li>Run the following command to install the `ChatterBot` and `chatterbot_corpus` libraries:</li>
    <pre><code>pip install chatterbot chatterbot_corpus</code></pre>
</ul>
</details>

<details>
    <summary style="font-weight: 800;">Step 2: Create Your Chatbot <img alt="Create" width="20" src="https://img.icons8.com/material-outlined/24/000000/create.png"> </summary>

<h3><ins>Overview</ins></h3>
<p>In this step, you’ll create a Python script to define and train your chatbot. This script will also include a loop for interacting with the chatbot.</p>

<h3><ins>How to Create Your Chatbot</ins></h3>
<ul>
    <li>Create a new Python file, e.g., `chatbot.py`.</li>
    <li>Add the following code to set up and train your chatbot:</li>
    <pre><code>
from chatterbot import ChatBot
from chatterbot.trainers import ChatterBotCorpusTrainer

# Create a new chatbot instance
chatbot = ChatBot('SimpleBot')

# Create a new trainer for the chatbot
trainer = ChatterBotCorpusTrainer(chatbot)

# Train the chatbot on the English language corpus
trainer.train('chatterbot.corpus.english')

# Function to get a response from the chatbot
def get_response(user_input):
    return chatbot.get_response(user_input)

# Run a simple loop to interact with the chatbot
if __name__ == "__main__":
    print("Hello! I am a simple chatbot. Type 'exit' to end the conversation.")
    while True:
        user_input = input("You: ")
        if user_input.lower() == 'exit':
            print("Goodbye!")
            break
        response = get_response(user_input)
        print(f"Bot: {response}")
    </code></pre>
</ul>
</details>

<details>
    <summary style="font-weight: 800;">Step 3: Run Your Chatbot <img alt="Run" width="20" src="https://img.icons8.com/material-outlined/24/000000/run.png"> </summary>

<h3><ins>Overview</ins></h3>
<p>Now that you’ve created your chatbot, you’ll run the script to see it in action. This step will allow you to interact with your chatbot and test its responses.</p>

<h3><ins>How to Run</ins></h3>
<ul>
    <li>Save the `chatbot.py` file.</li>
    <li>Run the script using the terminal or command prompt:</li>
    <pre><code>python chatbot.py</code></pre>
    <li>You should see a prompt where you can interact with your chatbot. Type messages to see how it responds.</li>
</ul>
</details>

<details>
    <summary style="font-weight: 800;">Step 4: Customize Your Chatbot <img alt="Customize" width="20" src="https://img.icons8.com/material-outlined/24/000000/customize.png"> </summary>

<h3><ins>Overview</ins></h3>
<p>Enhance your chatbot by adding custom responses. This step will show you how to personalize your chatbot to make it more engaging and useful.</p>

<h3><ins>How to Customize</ins></h3>
<ul>
    <li>Modify the training data by adding custom responses:</li>
    <pre><code>
from chatterbot.trainers import ListTrainer

custom_trainer = ListTrainer(chatbot)

custom_conversations = [
    "Hello!",
    "Hi there!",
    "How are you?",
    "I'm good, thank you!",
    "What is your name?",
    "I am a chatbot created by Harish."
]

custom_trainer.train(custom_conversations)
    </code></pre>
    <li>Add this code before your interaction loop in `chatbot.py`.</li>
</ul>
</details>

<p>Congratulations! You’ve built a basic AI chatbot using Python. This simple project introduces you to the core concepts of AI and natural language processing. Feel free to experiment and customize further to explore the endless possibilities of AI.</p>

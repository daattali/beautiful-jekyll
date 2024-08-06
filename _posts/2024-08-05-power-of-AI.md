---
layout: post
title: How to Build a Simple AI Chatbot
subtitle: A Hands-On Guide to Creating Your First AI Chatbot
cover-img: "assets/img/ai.jpg"
date: 2024-08-04 01:01:00 IST
tags: [ai, python, chatbot]
comments: false
author: Harish Sarma
readtime: true
---

Below, you’ll find a step-by-step guide to building a simple AI chatbot using Python. This guide is designed to help you get started with AI and create a functional chatbot that you can customize and expand upon.

**Here’s What You’ll Learn**:

Follow the instructions to build your chatbot and learn how AI can be applied in real-world scenarios.

### Step 1: Set Up Your Environment

**Overview**

First, you need to install the necessary Python library to get started with building your chatbot. This setup will ensure that you have the tools required for the project.

**How to Install**

- Open your terminal or command prompt.
- Run the following command to install the `ChatterBot` and `chatterbot_corpus` libraries:

    ```bash
    pip install chatterbot chatterbot_corpus
    ```

### Step 2: Create Your Chatbot

**Overview**

In this step, you’ll create a Python script to define and train your chatbot. This script will also include a loop for interacting with the chatbot.

**How to Create Your Chatbot**

- Create a new Python file, e.g., `chatbot.py`.
- Add the following code to set up and train your chatbot:

    ```python
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
    ```

### Step 3: Run Your Chatbot

**Overview**

Now that you’ve created your chatbot, you’ll run the script to see it in action. This step will allow you to interact with your chatbot and test its responses.

**How to Run**

- Save the `chatbot.py` file.
- Run the script using the terminal or command prompt:

    ```bash
    python chatbot.py
    ```

- You should see a prompt where you can interact with your chatbot. Type messages to see how it responds.

### Step 4: Customize Your Chatbot

**Overview**

Enhance your chatbot by adding custom responses. This step will show you how to personalize your chatbot to make it more engaging and useful.

**How to Customize**

- Modify the training data by adding custom responses:

    ```python
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
    ```

- Add this code before your interaction loop in `chatbot.py`.

Congratulations! You’ve built a basic AI chatbot using Python. This simple project introduces you to the core concepts of AI and natural language processing. Feel free to experiment and customize further to explore the endless possibilities of AI.

<p> Feel free to discuss anything, share your ideas, or seek assistance with any shortcuts-related issues. Your thoughts and questions are always welcome! If you love these shortcuts, please drop a ❤️. </p>
<p> Join the conversation by clicking here 👉🏻 <a href="https://github.com/harishsarmav/HarishHub/discussions/2" class="btn" style="color: white; background-color: #82B5F3;">Discussions</a> </p>
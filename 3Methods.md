---
layout: page
title: Models & methods 
subtitle: what we used, how and why
---

<h1 id="#LLM">LLM for violence classification</h1>

<p>
Movies are classified between different violence level using a custom prompt and function for the model <a target="_blank" href="https://platform.openai.com/docs/models#gpt-4o-mini">GPT-4o mini</a> from OpenIA. 
</p>

<p>
For the data, we create batch by concatenating multiple plots by adding a separator with the plot number between each plot. Testing reveal that the model tends to forget some plots if to much are given at the time. We stated on batch on 10 movies, taking care of the maximum tokens number of the model. 
</p>

For the model, we processed as follow :
<ul>
    <li>Create a custom violence scale , a set and instruction and provide examples</li>
    <li>Create a custom function to specify the return format of the model </li>
    <li>Create a request for the model</li>
</ul>

We followed the <a target="_blank" href="https://platform.openai.com/docs/guides/prompt-engineering">prompt engineering guide</a> of openIA to design the scale and examples.

<details><summary>Prompt</summary>
<code style="color: red">
  ### Violence scale : ### <br/><br/>

  - **Peaceful**: The text describes no physical or psychological violence. There are no aggression, conflict, or harm to people or animals. Suitable for all audiences.<br/>
  - **Mild**: The level of violence is medium or uncertain. There might be moments of tension or mild conflict, such as arguments. Mild action or suspense is allowed.<br/>
  - **Violent**: The text describe extreme physical or psychological violence, such as physical aggression, conflict, or harm. Scenes may include fighting, injury, rape. It a prominent feature of the film.<br/><br/>

### Instructions ### <br/><br/>
Assign a level of violence to each plot movie plot below. Respond with a dictionary where the keys are the plot numbers (e.g., 'plot1', 'plot2') and the values are the levels of violence ('Peaceful', 'Mild', 'Violent')</code></details>
<details><summary>Example</summary>
 <code style="color: red">
    Here are some examples for each label : <br/>
        - **Peaceful**: plot1 :'norma and malcolm miochaels are a middle-aged married couple who are in the midst of a midlife crisis. both decide to separate and begin their lives anew away from each other. however, problems ensue once they discover that they are no longer as young as they used to be.'
        plot2:'in the 1840s, two sisters fall in love with the same man. while drunk, the man writes a letter proposing marriage to the wrong one.'<br/>
        - **Mild**: plot1:'set in the 19th century, the plot centered around a man  who is falsely accused murder. the other side of the door was shot in monterrey, mexico.{{cite web}}'
        plot2:'in a desperate, but not-too-courageous, attempt to end his life, a man hires a murderer to do the job for him. soon, though, things are looking better and the he must now avoid the hit.'<br/>
        - **Violent**: plot1:'Richard Beck  is a police detective who believed that rape victims are to blame for the crime. He is later raped by two of the suspects he had been chasing. Ultimately, he changes his beliefs about rape victims. This made for TV movie was groundbreaking in that it portrayed the rape of a man by two other men, and because of this it has become a cult classic.'
        plot2:'newlywed carl  goes to war where he endures major suffering. back home, wife pauli  starves, becomes a prostitute to survive, and their baby dies.'
  </code></details>

We want the model to return a array of prediction, one prediction per plot. We specified a task and a return type using a function.

<ul>
    <li>Assess the maxim</li>
    <li>Create a custom function to specify the return format of the model </li>
    <li>Create a request for the model</li>
</ul>

<h4>Custom function for classification</h4>

```ruby
self.function = {
"name": "Assign_violence_level",
"description": "Predict the level of violence of a list of movie plots",
"parameters": {
    "type": "object",
    "properties": {
        "prediction": {
            "type": "array",
            "items": {
                "type": "string",
                "enum": [
                    "Peaceful",
                    "Mild",
                    "Violent"
                ]
            },
            "description": "The list of violence levels for each movie plot, in the same order as the plots were provided."
        }
    },
    "required": [
        "prediction"
    ]
}
}
```

Finally, we create the request by combining all elements. 

<h4>Create a request</h4>

```ruby
completion = self.client.chat.completions.create(
    model="gpt-4o-mini",
    messages=[
        {"role": "system", "content": self.Content},
        {"role": "user","content": Text},
        {"role": "assistant", "content": self.Example}
    ],
    functions=[self.function],
    function_call={"name": "Assign_violence_level"},
)
```

<h1>Sentiment analysis</h1>

<h1>Empath model</h1>

<h1>Auto-regressive distributed lack model</h1>
 
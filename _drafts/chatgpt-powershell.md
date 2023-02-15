## Create an OpenAI API token

* First we need to create an API key. For that, go to your account profile and click on **View API keys**

![openai profile](/img/2023-01-25-13-36-46.png)

* Then click **Create new secret key**

![create openai api key](/img/2023-01-25-13-37-17.png)

* Copy the key in the clipboard, you won't be able to display it again. If you close without copy9ng, you'll have to create a new one.

![copy api key](/img/2023-01-25-13-38-05.png)

* Now let's export that key in an environment variable in the Powershell session.

``` Powershell
$env:OPENAI_API_KEY = "sk-Wif...BzndkO"
```

## Powershell function for ChatGPT

When starting with this blog idea, I went to the API documentation straight away but... wait a minute! I decided to do a bit of dog fooding and ask ChatGPT to write the function for me and the result was really good! I had to change a couple things here and there but here is the ChatGPT Powershell function.

``` Powershell
function Ask-ChatGPT {
    param(
        $prompt,
        $model = "text-curie-001",
        $api_key = $env:OPENAI_API_KEY,
        $max_tokens
    )

    # Build the request body
    $body = @{
        "prompt" = $prompt;
        "model" = $model;
    }

    if ($max_tokens) {$body.add("max_tokens",$max_tokens)}

    # Send the request
    $response = Invoke-RestMethod -Uri "https://api.openai.com/v1/completions" -Method Post -Headers @{ "Authorization" = "Bearer $api_key";"Content-Type" = "application/json" } -Body (ConvertTo-Json $body)

    # Return the response
    return $response.choices.text
}
```

* The `$model` parameter lets you change the [OpenAI model](https://beta.openai.com/docs/models/overview) to use. Different models will be more or less advanced and expensive regarding to your needs. I set it to `curie` by default partly because their doc says it's very good and partly because I have no idea what I am doing.

>Curie can perform many of the same tasks as Davinci, but faster and for 1/10th the cost.

![openAI language models](/img/2023-01-25-15-03-05.png)

* The `$max_tokens` parameter lets you set a maximum number of [tokens](https://openai.com/api/pricing/#faq-token). A token is essentially a piece of word. Requests are billed based on the number of tokens sent in your prompt plus the number of tokens in the completion returned by the API. The models above are priced based on chunks of 1000 tokens.

## Use ChatGPT in Powershell

Before cracking on, I should mention that you may encounter an error saying that you don't have enough funds, even though every new user is entitled to $18 worth of free usage. I believe this was because ChatGPT was down at this time and the error was just not reprensentative of the situation.

```
"message": "You exceeded your current quota, please check your plan and billing details.",
"type": "insufficient_quota",
```


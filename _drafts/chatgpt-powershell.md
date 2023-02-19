## Create an OpenAI API token

* First we need to create an API key. For that, go to your account profile and click on **View API keys**

![openai profile](/img/2023-01-25-13-36-46.png)

* Then click **Create new secret key**

![create openai api key](/img/2023-01-25-13-37-17.png)

* Copy the key in the clipboard, you won't be able to display it again. If you close without copying, you'll have to create a new one.

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

## You exceeded your current quota, please check your plan and billing details

Before cracking on, I should mention that you may encounter an error saying that you don't have enough funds, even though every new user is entitled to $18 worth of free usage. I believe this was because ChatGPT was down at this time and the error was just not reprensentative of the situation.

```
"message": "You exceeded your current quota, please check your plan and billing details.",
"type": "insufficient_quota",
```

It seems that OpenAI changed the policy and made the API available to paid accounts only. I was able to use the web UI fine but I would get this message when using my API key. I just added a payment method in my account and it worked fine.

![set up paid account chatgpt](/img/SCR-20230219-jkv.png)

I couldn't find the $18 trial credit in my account so I just set a spending limit of $5 just to make sure it won't drain my hard-earned monies.

![chatgpt spending limit](/img/2023-02-19-15-31-20.png)

Before you freak out about expecting a big invoice like you heard it happen to folks playing in AWS, note that it remains very cheap if you use it sparingly. As you can see, I only did 15 requests but quite a few of them had lenghthy responses and I have only used $0.01.

![chatgpt monies](/img/SCR-20230219-lay.png)

## Using ChatGPT in Powershell

Using the function is very simple, just run `Ask-ChatGPT` with your question. The only extra parameters I added is `-model` (which we'll discuss later) and `-max_tokens`. According to the documentation, the default max_token value is 2048 (max) but I found that the responses were always cropped if I didn't specify it. As a result, if you find that your queries get cropped, set `-max_tokens` to a high value. If you set it too high, the error message in the output will help you adjust it.

And as mentioned earlier, you do need to have set `$env:OPENAI_API_KEY` with you OpenAI API key.

Here is a simple use case with the default model and max_tokens which works as the response is short.

``` powershell
PS /Users/xavier> Ask-ChatGPT "write a PowerCLI command to list free space on all datastores as a table"


Get-Datastore | Format-Table --AutoSize FreeSpace
```

## Which model to choose?

As we mentioned earlier, there are several models with different prices. Some are more advanced than others, hence the higher price tag and we are about to see why. You will find that there can be quite a big different in results quality depending on which model you use. I configured the `Ask-ChatGPT` function with `text-curie-001` as default but you will find that it isn't always up to the task if the request gets too complicated. 

The example in the previous chapter for was fine `curie` as it was an easy use case. However, let's try to ask something a bit trickier. In this case, I'm asking ChatGPT to write a Powershell function to get the weather using the Openweathermap API. I chose this task because I did it myself several years ago as part of a [blog](https://www.bdrsuite.com/blog/powershell-functions-to-leverage-a-rest-api/) about using Rest APIs in Powershell.

### Curie model

Let's first try with the cheaper `Curie`. As you can see, it produced a load of garbage that probably doesn't work (didn't bother testing it). 

``` Powershell
PS /Users/xavier> Ask-ChatGPT "write a Powershell function with cariage return to get the weather using the openweathermap API" -max_tokens 2020


$action = "GET"
$location = "https://openweathermap.org/api/2.0/weather/GET_STATION"
$w = New-Object System.Net.WebClient
$url = $location
$c = $w.DownloadString( $url )
$weather = $c.DownloadString()

$return = $action.ContinueWith(

{
$url = "https://openweathermap.org/api/2.0/weather/$location"
$c = New-Object System.Net.WebClient
$url = $location
$v = $c.DownloadString( $url )
$weather = $v.DownloadString()

if ($weather -ne "")
{
# get temperature
$temperature = $weather.Temperature.To Celsius()
}
else
# get weather conditions
$return = $action.ReturnResult
$return = $return.ToString()

# set the return values
$return = $return.replace("Temp", "temperature")
$return = $return.replace("Conditions", "weather_conditions")

 write-host "Temperature: $temperature"
write-host "Weather Conditions: $return"
```

### Davinci model

Now using the more expensive `Davinci` model, we get a nice and efficient function. While the price per token is higher than curie's, the response is much shorter (in this instance), which means it might even be cheaper as it requires less tokens but I didn't do the math. Plus, I just wasted a bunch of tokens as the first reply is of no use. 

``` Powershell
PS /Users/xavier> Ask-ChatGPT "write a Powershell function with cariage return to get the weather using the openweathermap API" -max_tokens 2020 -model "text-davinci-003"


Function Get-Weather {
    [CmdletBinding()]
    Param
    (
        [Parameter(Mandatory=$true)]
        [String]$APIKey,
        [Parameter(Mandatory=$true)]
        [String]$City
    )

    $WeatherData = (Invoke-WebRequest -Uri "http://api.openweathermap.org/data/2.5/weather?q=$City&APPID=$APIKey").Content
    Return ConvertFrom-Json $WeatherData
}
```

I believe choosing a model isn't easy feat as it will probably require a bunch of testing for your specific use case to figure out which one works for you and in the end select the cheapest.

## Wrap up

And there you have it, a function that will let you ask ChatGPT from the comfort of your PowerShell prompt so your colleagues don't catch you asking an AI to do your job! This was a pretty quick and dirty job and a lot more features could be added but I'd say it's a pretty good starting point.

On a side note, if you are looking for options on how to **protect your vSphere and VMware Cloud Director** workloads, [Nakivo Backup & Replication](https://www.nakivo.com/) offers capabilities to back up vSphere VMs and VCD objects such as vApps, individual VMs and vApp metadata and ensure that remote workloads can be recovered in case of a data loss event.

[![nakivo backup](/img/2022-10-26-13-45-41.png)](https://www.nakivo.com)
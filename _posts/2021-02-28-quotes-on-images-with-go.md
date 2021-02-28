---
layout: post
published: true
title: 'Putting Text on an Image with Golang'
subtitle: 'Running it locally, on GCP or Heroku easily'
date: '2021-02-28'
image: /assets/img/devs-quotes-logo-black.png
share-img: /assets/img/devs-quotes-logo-black.png
tags: [golang, heroku, gcp]
---

Since the beginning of my career, I have been focused on Java as my main programming language, but recently I switched to a company that uses Golang, and to help me to learn more about the language I decided to build something. 

The service that I build in summary just puts some text on a given image. Its main purpose is to help me create the posts that I publish on my Instagram account [DevsQuotes](https://www.instagram.com/devsquotes/). 

I used to create my posts with Photoshop but it was taking me too much time to get a simple image ready, then I discovered [Adobe Spark](https://www.adobe.com/es/products/spark.html) which simplified the flow a little, but with this service now is super simple since I integrated it with a Telegram Bot and now I just need to send a message and I have my image ready to be published. Yes, there is room for improvement, but keep in mind that this was just a PoC which mission was to help me get comfortable with GoLang and simplify the process to create images for my Instagram.


## TL;DR Show me the code!

```
type Request struct {
	BgImgPath string
	FontPath  string
	FontSize  float64
	Text      string
}

func TextOnImg(request Request) (image.Image, error) {
	bgImage, err := gg.LoadImage(request.BgImgPath)
	if err != nil {
		return nil, err
	}
	imgWidth := bgImage.Bounds().Dx()
	imgHeight := bgImage.Bounds().Dy()

	dc := gg.NewContext(imgWidth, imgHeight)
	dc.DrawImage(bgImage, 0, 0)

	if err := dc.LoadFontFace(request.FontPath, request.FontSize); err != nil {
		return nil, err
	}

	x := float64(imgWidth / 2)
	y := float64((imgHeight / 2) - 80)
	maxWidth := float64(imgWidth) - 60.0
	dc.SetColor(color.White)
	dc.DrawStringWrapped(request.Text, x, y, 0.5, 0.5, maxWidth, 1.5, gg.AlignCenter)

	return dc.Image(), nil
}
```

That piece of code makes all the magic. With the help of [Fogleman library](https://github.com/fogleman/gg) manipulating images in Go is a breeze. Let's check what this is doing:

```
bgImage, err := gg.LoadImage(request.BgImgPath)
```

It loads the image in which the text will be printed.

```
imgWidth := bgImage.Bounds().Dx()
imgHeight := bgImage.Bounds().Dy()
```

Records the `Width` and `Height` of the image.

```
dc := gg.NewContext(imgWidth, imgHeight)
dc.DrawImage(bgImage, 0, 0)
```

Creates something like a canvas (or context) in which we are going to start working.

```
dc.LoadFontFace(request.FontPath, request.FontSize)
```

It loads the font to use on the message to be printed.

```
x := float64(imgWidth / 2)
y := float64((imgHeight / 2) - 80)
```

Records the middle of the image on X and in Y it also subtracts 80 because I want the text to be a little bit above the middle.

```
maxWidth := float64(imgWidth) - 60.0
```

We define the maximum width that your text can occupy. Subtracting 60 from the total width of the image is like generating a margin, so our text does not reach the edge of our image.

```
dc.SetColor(color.White)
```

We are defining the color in which we are going to _paint/print_

```
dc.DrawStringWrapped(request.Text, x, y, 0.5, 0.5, maxWidth, 1.5, gg.AlignCenter)
```

It prints the content of `request.Text` on our canvas in the middle of the image with an alignment centered. 

The result will look like this:

![PrinterExample](/assets/img/accurate_measurement.jpeg)

For more context on how all this works and even try it by yourself if you want visit [the DevsQuotesPrinter repository](https://github.com/JosemyDuarte/DevsQuotesPrinter). It has instructions for you to be able to deploy it on GCP, Heroku or to try it locally, so feel free to play with it.
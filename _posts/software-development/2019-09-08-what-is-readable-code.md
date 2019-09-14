---
layout: post
title: What Is Readable Code?
category: software development
tags: [processes]
---

> Code creates interfaces. But code itself is also an interface.

For something so important, code readability is shockingly ill-defined. We often present it as a grab bag of rules: Use expressive variable names. When a function gets big, split it into smaller functions. Use standard design patterns.

But we’ve all seen code that follows the rules and is still, somehow, a mess.

We might try to solve this problem by piling on more rules: If variable names are getting extremely long, refactor the underlying logic. When one class accumulates tons of helper methods, maybe it should have been two. Don’t use design patterns in contexts where they don’t fit.

The guidelines turn into a maze of judgment calls, requiring a developer who can pick and choose. In other words, a developer who already writes readable code.

So there’s another piece of the puzzle here. To find it, we’ll need to build a broader picture of readability.

# What’s readability for, anyway?

In practice, readability usually boils down to “I like reading it.” This isn’t a great heuristic. Besides being subjective, it gets tangled up in our past experiences with reading.

Unreadable code reads like a novel trying to pass itself off as code. Covered in long narrative comments. Files packed with text, to be read in sequential order. Cleverness for the sake of being clever. Lack of word reuse. The code is trying to be readable, but it’s targeting the wrong kind of readers.

There’s a difference between readability and code readability.

> Code creates interfaces. But the code itself is also an interface.

Is code readable when it looks pretty? Looking pretty is a nice side effect of readability, but it’s not that useful. Maybe on the margins, it helps with employee retention. But so does a good dental plan. Plus, everyone has a different opinion of what “looks pretty.” Soon enough, this definition of readability spirals into a vortex of tabs, spaces, braces, camel casing, and the other formatting holy wars. No one will faint upon seeing misaligned arguments, despite the attention they attract during code review.

Is code readable when it generates fewer bugs? Having “fewer bugs” is good, but what’s the mechanism here? The warm fuzzy feelings someone gets when they see readable code? Reading can’t summon bugs, no matter how powerfully the reader is frowning at the code.

Is code readable when it’s easier to edit? The ease of editing sounds like the best reason. Requirements change, features get added, bugs appear, and eventually someone will need to edit our code. In order to edit it without causing issues, they need to understand what they’re editing and how their edits will change the behavior. This gives us a new heuristic: Readable code should be easy to edit safely.

# What makes code easier to edit?

At this point, we might feel a compulsion to rattle off rules again. “Code is easier to edit when the variable names are expressive.” Nice try, but all we’ve done is rename “readability” to “ease of editing.” We’re looking for new insights here, not the same rule-by-rule memorization in a fake mustache and wig.

Let’s start by setting aside the fact that we’re talking about code. Programming has been around for a couple decades, a dot on the timeline of human history. If we restrict ourselves to that dot, we’re drawing our ideas from a shallow well.

Instead, let’s look at readability through the lens of interface design. Our lives are filled with interfaces, digital and otherwise. A toy has features that make it roll or squeak. A door has an interface that lets it open, close, and lock. A book arranges data in pages, allowing for faster random access than a scroll. Formal design training tells us even more about these interfaces; ask your design team for more information. Failing that, we’ve all used good interfaces, even if we don’t always know what makes them good.

Code creates interfaces. But the code itself, together with its IDE, is also an interface. This user interface is aimed at a very small population of users: our teammates. For the rest of this post, we’ll refer to them as “users,” to stay in the headspace of UI design.

With that in mind, consider some sample user flows:

- •The user wants to add a new feature. To do this, they must find the right spot and add the feature, without also adding bugs.
- •The user wants to fix a bug. They’ll need to find the source of the bug and edit the code so it stops happening, without introducing different bugs.
- •The user wants to verify an edge case acts a certain way. They’ll want to find the right code, then trace through the logic to simulate what would happen.

And so on. Most flows follow a similar pattern. We’ll be looking at concrete examples for ease of understanding, but remember, we always want to keep the general principles in mind, rather than falling back to a list of rules.

---

We can assume that our users won’t be able to beeline to the right code. This goes for hobby projects too; it’s easy enough to forget the location of a feature, even if I’m the one who originally wrote it. So our code should be searchable.

If we’re supporting search, we’re going to need some SEO. Expressive variable names come in here. If the user can’t find a feature by moving up the callstack from a known point, they can start typing keywords into search. Now, not every name needs to have every keyword. When our users search for code, they only need to find a single entry point and can work outward from there. We need to get them close to where they want to be. Include too many keywords, and they’ll be frustrated by noisy search results.

# If the user can immediately convince themselves that ‘this level of logic is correct,’ they’re able to forget all previous layers of abstraction, freeing up mental space for subsequent layers.

Users may also search via autocompletion. They have a general idea of what function they need to call or what enum case they want to use, so they’ll start typing and pick the autocomplete that makes sense. If a function is only meant to be used in specific cases or has caveats that require careful reading, we can signal that with a longer name. When the user is reading the autocomplete list, they’ll typically avoid the complicated-looking option unless they know what they’re doing.

Likewise, short, generic names are likely to be viewed as the default option, suitable for casual users. Make sure they don’t do anything surprising. We shouldn’t put setters into simple-looking getters, for the same reason a customer-facing UI wouldn’t show a “View” button that mutates their data.

![](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/54078083-30be-4efb-89bf-5fdbab5930ef/1ofG2DvHDrMYfl2qrz4e4LQ.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=ASIAT73L2G45LOZHAZYR%2F20190817%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20190817T162431Z&X-Amz-Expires=86400&X-Amz-Security-Token=AgoJb3JpZ2luX2VjEMX%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJHMEUCIBhcq1ilCNEyaAPAkt%2B%2FqNAgykuj2xGozm8Q6u4kC4tBAiEAl%2BxVQk%2BlAe%2F4u4MFfIWfCEKCTQmux93zGSbWFxUKmYcq2gMIXhAAGgwyNzQ1NjcxNDkzNzAiDDuz2QKX9q0rvdKSSSq3A2ga98CFzvIUn3ql7y1pNpUVZADzHCXOm%2BWnq1C3hW2d1R4LE8pFd%2B%2B3K3hHKFdDRiIXGbZM3tl6DYYakyNNkXRLWV3D5U7SyO%2FcSzX0Ea0qlwTPPVLHwRiIyonBSHTSSDvYAhGwmHCAxP5rwW7%2FDLsWx4Cj6N76Fcnlm0qK%2BIsV9qkqHPipP7h79XbTTE%2Bbc1ohO8Z6hgY6uoG%2F7oNMv%2B0PalHgZj62svfhY2e6sBNpQer3yh%2FDVezOXGcK8SKnQuC3eOf3oec9QXJhAfV5105YH9ETiHOsogSGw898Jw2xbc3JkxHqbdnbgH0cbymPt8R%2FbALTi%2F4DlzJ%2FnYI9uvspw7ZX3vxj1%2FPkys1ZCrtPQRh6PznOQq8vwEQVjl%2F7ih%2F%2BucHKgjK5IUtLL14hhj%2BfgYH2Ho3my5%2F8Hz9qX9gycIg7aTflqn9lkNay%2BNdNOy8G93NPR0X1xXxWgTxLRtWB9L2JcJmFPE2BWOwtBiT9qIrmmOYbC8xvDDLFWJQGgjUqu85fv7VUqdvUrxABuuCWThdKG1VdedS47UFHCszWYuPthftmi7IpFXBB0uM3troSHxCXj2AwsPzf6gU6tAFbaapvgFVR6Yy459rD4ODsfD%2Fl3hEYhov1La9TKBJLPCslcZkn3pTDor9Dh8Nrgj2BXs0NNcN4%2BBCPraS4mhC1MO4zOT1815gVgYdte0DQ%2BPgtCP5H51N%2FaeXS8ug4kRHchajbD6TUm1qvYYY7J4IQR9QY%2BtPZHH%2Bp9mi3RzbH8BNF58ZACqkknRLcnUZyqnI4Kgm2vfrYYuInJRYQx2YiZsg7STEB3883miYJFlxyY%2F8AsBM%3D&X-Amz-Signature=8e9feaae802bc40e071c57e899a85aeef539acd67e6e6e4b5e94997ad75990ad&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%221ofG2DvHDrMYfl2qrz4e4LQ.png%22)

![](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/9b202f51-2148-453c-8500-30a3f3414ad3/1Gd-N0tP7qVDkcQ0SfZWgqQ.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=ASIAT73L2G45DIKQSRRV%2F20190817%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20190817T162457Z&X-Amz-Expires=86400&X-Amz-Security-Token=AgoJb3JpZ2luX2VjEMX%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJIMEYCIQCnDtcgNFHTHKXsOc%2BT7zlU5vT4HqF8gIg0iao476HJBwIhAPhXm4LzrOMtNL5HnPyWqMBrjW4VtYgV%2Ftb%2BgvqedMWzKtoDCF4QABoMMjc0NTY3MTQ5MzcwIgz9pqa6BrQoLBZkM8kqtwNUzZMsSdPzSLIvERUQ6cN7EXIB2eVLHbKEZHfb0kLwGtSP5DwrY%2ByCVynGfHCnD5fkUW2kogtSo81BaKUEwdtOC%2BCl73N59dCs2efXI3sQptLLzffFteYuCi48ulXxIaM8NvYDKjx0pENHrBKFvkK%2F2ozet5CUIgVqYEMhn9pzqUpPCXVfvTRqccjsGsjOxntA4YwHrjw5z0dR%2FQ5i0Gf0DFfbTJ%2FoSRyP%2B6VsP2RX0ffAXzeHrl8cKy%2FXGsp2yjo1it5Oa38aj5VnqNLmPrsJWN3zaGDC8HYy%2FZyua%2F4jJ99bl%2BuXVahVGrl%2B1yNgGtVcqaxZxvcVXUL0r5xB6VatEkeYXeEBwi14pibzNtLk%2BT8Bo4vgu9%2F7JwDBNoYhEOphhxKdpg2pXaXKOLqijHo8FUB1t%2Bdi7jCF0BJkq77cL%2BgBeMnX1zpuiv8gqSQa08aCeAThfi9M31fC5caowP0MbZ8ZyymY%2BGdY9aoWFyGIwdMpE%2BHRJcIp%2FDiCVAKldymcU9G7IAZi7gqntixpzCi674Pju11S3ijSE1BFiOxL17DKvNFTXCLdh3UZfN2vc7MXfo2hZJ5wMLrp3%2BoFOrMBW7%2FL00y0w6idjqn1rm9j9GCz6tkCG6FOkSoNLMRJEoIqgwjCQE0s9lWIAl3g8WurfM63m870IAPKLRAXAvvYGpw2jApuJpyAglToCPbVL8Z0bN%2Bf%2Bri6HKfWWFwgBfC6m4VQ1KfWpX6hZNLYz9PTclmPCwvF62phgfy7mfRBclgsk6B73zOAfRNwgC9NQcvgTD303%2F60x6MND%2BpiqO2gKJb5%2Fy4HNuldPfi8CEJ2LBuW%2BPU%3D&X-Amz-Signature=7c8c2184625b7f5aba7ae684b6110404f7ba0d1cfed24080d5ac278e5f6f4d17&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D"1Gd-N0tP7qVDkcQ0SfZWgqQ.png")

In a customer-facing UI, common options like pause have little to no text. As options get more advanced, the text gets longer, prompting users to slow down. Screenshot: Pandora

And they’ll want to find that information at a skimming pace. In most cases, compiling takes time, and running may require manually visiting many, many different edge cases. When possible, our users would prefer to read the code’s behavior, rather than throwing in breakpoints and running the code.

To skip running, they need to satisfy two conditions:

1. 1 "."They understand what the code is trying to do.
2. 2 "."They’re confident that it’s doing what it claims.

Abstraction helps satisfy the first condition. Users should be peeling back layers of abstraction until they reach their desired level of granularity. Think along the lines of a hierarchical UI. We allow users to make large navigations first, then more precise ones as they get closer to the logic they want to read in detail.

Sequentially reading through a file or method takes linear time. As soon as the user can click up or down through callstacks, they’ve switched to doing a tree search. Given a well-balanced hierarchy, that only takes logarithmic time. Lists have their place in UIs, but consider carefully whether a single context needs to contain more than a couple of method calls.

![](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/968913e7-4f7a-4767-9f41-c6783daa6b21/1DrKugQypQppWXIiwL-Ep0Q.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=ASIAT73L2G45NWLB5LMG%2F20190817%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20190817T162534Z&X-Amz-Expires=86400&X-Amz-Security-Token=AgoJb3JpZ2luX2VjEMX%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJIMEYCIQDS%2FPuM%2FQhzerc4pJ7bM6t%2Ba4gvlKNHvO3TSsp3q3E13wIhAIg0yG8v%2FWdOCjytZ8GwsnpPnwG22PJCbioqBv22tg1WKtoDCF4QABoMMjc0NTY3MTQ5MzcwIgzp1D68COUWFlXHhCoqtwONs%2BtHR0oPgLQOuctPbz0cSq5GER0FY9bmwhw9lXaijGhZTBXpRaYk8poisL5CYrST1G9Pw%2BNcZRWH6hGMQY9T0kJYwecddZQK9Yu8LxTGhV935rFJih5q2p0Aahjp5jZMUhbjmvUOmiSYXEXtAvQHJ%2Fg4lgJ40JIQldJfHaCN2JE1HqdOQ1zs3hz6AJnBUOwWIcDecOcJZEU%2B9eqgRg8ujXRrVwhHsGpHqYOvAHLanxNpbpuQVpD29m4vxPkA6ZEMQC79qM2ecu33Q7EVIE5cv701kc%2FcYT4EFj5MN2TGQVpYelpMaNGMPmsnifYd3GGBNj95lkoH9EkDP9CEuoB3Oc8N3lqeVVx8c9fF49GaO5HUVLV2%2FRneMCx6zWMnx7Ow06g1KATvUp56QXF2dI%2F3xNGLnhBRGihFPho9rcDSTeJarhHrv%2FO%2FpFyVOfrcrwFhOra%2FAOy6tUl9%2BNM4CjAOXlKoj9OiDwLegn3v8zFUjIt%2F3zOxVltRKaM3LIjB4Z7Lpf5cjpUuXAd9NfXFBxbjT8zmlvLqEpkv0Xdjp3i%2FTV0DCQRkQoh1ace8xPKrk7LoUTzlV0eXMMHz3%2BoFOrMBwLbASpzh6bmF4tjw%2FL51PYH5dwKLOvjpDedTRq9RdQkX2CUwDGVDranjss5%2FHq04DEWSJamPs%2FBj5%2FKrVqZ%2BzYccJObH5rny7u6XXRLCHgshJZvX68fPPKC%2Bto%2FmdVWtmrODaiFpbOSV52cwWojnSbfOub1%2FHoECwmxF3lUC40y%2BgAyYrxQf5rw3HmPlCINU8LNMt0NAbnmYoIFoGIPn9XyAW4M2MeeOdGDEl4HU%2FBrJdPI%3D&X-Amz-Signature=be88e1c3501b863ccd47e1751af83c1154de855c42e2729a40b0517cd3020b9b&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D%221DrKugQypQppWXIiwL-Ep0Q.png%22)

![](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/b7674087-4b0d-4cd3-a333-14e0940cf899/1fT17QnQtJhKy4DRBzCByZA.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=ASIAT73L2G45DTXMXGGR%2F20190817%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20190817T162629Z&X-Amz-Expires=86400&X-Amz-Security-Token=AgoJb3JpZ2luX2VjEMX%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJGMEQCIAzBsLn2yyWXtg7OJ4z4m7ElPbOrTvwpSC9hFTZzQjUSAiB0glQDMZ5a9AKphot93Rq36WynwlMkGZF8zVK8y1SSPCraAwheEAAaDDI3NDU2NzE0OTM3MCIMYMeiwzJwGXcNsWwPKrcDjSDv4fE5hRpw3JXWN9AOxdAE4q6esh1SAtDpe3yzDY0bZCuQ6pupo7jf7Fxr%2BrB9Y9x2V9M9fBPQpa2376%2FXpSmgAj%2FMGxthATIXsgPmPqAY%2BYt%2BtTRG%2FYUj%2B9kviDjtDdS8VozN8jMPh7Qrot2cc%2Bo6B1EZF0k3BPAwXMAuucHGHQG9%2FinQLruwtO0yiq5Wrgx93mMkNRZgcLeVoLi4pGR1GoiS4rPrml7ZEgTXEGC1dVhc9PUE0dAtQ3X4FY8phAdwOSiB3CBLoSVtYrX5h%2Bfnfpaf67N9n1Ef11qzIbUPYc19aTc6POsF7Mmo%2FQj6HfD8HT9MG2k7YOM943HbPPHPcpFIjYNbmY%2BiKsmDd6IJ2suowDW6MvIAFVbi4o2ihdk2Spzf1JaJub7h6FVZSUxBWs6yrq84QBrV0Dc9Q5m523PH4y2ruwWuGhp2oZfk0Xnj5livIgBH0gzASqpIbhajN%2FyUG5uR6zTuhDb7qRpnFY6p4Bokq%2FtDMENAC%2BhkNVdKO3G2QsM8bvNXabNQe06gaELWITYWxpBDAQ%2Fz5nob4N7QQFjb76ohagjQtb%2Fj6pfC0x5iVDC%2B%2FN%2FqBTq1AbpDkCdgVkw8rhE4m40BFiDahOW6J5honTfgc1XUsOFHnjkuNXScWppY9z9IBZ2wNg49KQ3txBhcnKenfU11gcHH0ScVUl2y1yUMhdZ9Wf3GzFud04Xenf3yBm6Btg48K3Fo7PWeSls29HSwRyaxvOc%2Fxg7QSozGEMeOVvvdaqTpzvdwTpKtIkVX5X2mW%2B50vNh%2BsGJRP8vJjQmHd8yF53G4V9zVRybe7BDpptyxes0JH9NFHDI%3D&X-Amz-Signature=9951dbfb9f60c2a44125aa2fb89b634705af50e28848a66dbbcf6c2aaa3b1b93&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D"1fT17QnQtJhKy4DRBzCByZA.png")

Hierarchical navigation is much quicker when there are fewer options in each menu. The ‘long’ menu on the right has only 11 rows. How often do we write methods with more lines? Screenshot: Pandora

For the second condition, different users have different strategies. In low-risk situations, comments or method names may be sufficient proof. For riskier, more complicated areas, or when users have been burned by stale comments, they’re likely to be ignored. Sometimes, even method and variable names will be met with skepticism. When this happens, the user has to read much more of the code and hold a larger model of the logic in their head. Small, easy-to-grasp contexts come to the rescue again. If the user can immediately convince themselves that “this level of logic is correct,” they’re able to forget all previous layers of abstraction, freeing up mental space for subsequent layers.

When the user is in this mode, individual tokens start to matter more. An **`element.visible = true`/`false`** bool flag is easy to parse in isolation, but it requires mentally combining two different tokens. If instead, the flag is **`element.visibility = .visible`/`.hidden`**, contexts involving the flag can be skimmed, without having to read the name of the variable to find out that it’s about visibility.¹ We’ve seen the same design improvements in customer-facing UIs. Over the past couple of decades, confirmation buttons have evolved from OK/Cancel to more descriptive options like Save/Discard or Send/Keep Editing. The user can figure out what’s going on by looking at the options themselves, rather than needing to read the whole context.

![](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/d6d09403-f4fc-4b81-b0df-a4b45726cee1/1Ky2UBTS_g0wy68dmVXkQ_A.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=ASIAT73L2G45EUEEQT2D%2F20190817%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20190817T162911Z&X-Amz-Expires=86400&X-Amz-Security-Token=AgoJb3JpZ2luX2VjEMX%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJHMEUCIQC6QLyr6gpAZ6vX0VtwVXC1P6mXB8k91kObWeWZXB2ofAIge%2BYjOHv21BCEBv0OefmgWKnHIdTm4eUigABjZr65Vv0q2gMIXhAAGgwyNzQ1NjcxNDkzNzAiDEP6xOpWigHQNc3i6yq3AymuoF3W2cDRozN79L9Re9cLPQrrDUmh7jFRHa1kcKW%2F9beVBFtV84hQsZzGOYO%2F3t%2BPocJOzM6vTwkaRKARpIuTsp7pvjJKiS9bC%2BXJZLlGvzKhdSxNoepNnaPXndkNdU5Yx97bCPaLcyM8P7JVUMuqXz4OYDICQ82u0IyxObAJh0LPEm5uTMozdqfXaO2PIDUZVrNaem8HrthB3zkuNZySOeqYY8YPQbnsTJ%2FxBr4Sy47A%2FEgUS4pFPMtWH8a2coA%2F6J9thP9RtBiZrfS30UOfECM%2F2z5zfd388C5QfpGwmlkc6x0rxxKhJyHZDNjVzup1pAwh5npX1lY1l1NWeAOFBgBbXkC8IMob1Umu5Q1jL3K9jF4AMOKvCh0U%2BohHR%2Bidb1T9vDzqvGx5tKnXKqqyohANsfnJsBvWmNdJxRa19sbeWP1Elivb6LNw2%2FeLLvXqXH%2Bof6NdD7iJlsKYSj7%2FzpWgbPr0OIcR5Fb91X2MAnwhkz3TLHV68LO31d%2F9%2Fs5R4fBcJNEEvvf%2FWWOXF6DR1QsQWZjuSeOI2rILTWkCYFVhw3Rb2HOqkDKb73cGkgrsPwR5YHIwkPnf6gU6tAGROsqEERAMvkNaiENfXkzbXwVoQMqhQwY9eshuXr2H09%2FhdWs7HFfUVvZs%2F77TXp5MlPdu1nhUiQKdDbp7iDFpr8VgLNWdo0IwXX%2BMHtVhWMuuje%2BPbf%2FUTHKwilXpyx7E2HigS8v3hEYAGS%2FvIs6he29In5BhNGncmj0%2B75TZ6RfK8X7kleHtGiCMWrNWJYVqIlT1GiaSFQvRfSZyEoLSfravW6QX5cOT758sOdXgA69fa%2Bk%3D&X-Amz-Signature=54b1fc6c8337146150c02cf6197ea5929356191a0e5ea1c40a6446c1b52788dd&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D"1Ky2UBTS_g0wy68dmVXkQ_A.png")

At a glance, the top ‘Offline Mode’ banner shows our current state. The bottom toggle conveys the same information, but only after looking at the context. Screenshot: Pandora

Unit tests can also help us past the proof-of-behavior condition. They act as more trustworthy comments because they’re less vulnerable to staleness. This still involves a build. However, any team with a good CI pipeline has already run the tests, so the user can skip this step for existing code.

---

In theory, safety comes from understanding. Once our user understands the current behavior of the code, they should be able to edit it safely. In practice, engineers are human. Our brains take the same shortcuts as anyone else’s brain. The less we have to understand, the safer our actions will be.

Readable code should offload most of the error-checking to a machine. Debug asserts are one way of doing this, though they require building and running. Worse, they may not catch edge cases if the user forgets about that path. Unit tests can be better at exercising commonly forgotten edge cases, but once the user has made changes, they also require time to run.

# In short, readable code must be usable. And maybe, as a side effect, it’ll look pretty too.

To get the fastest turnaround time, we use compiler errors. These rarely require a full build and may even appear in real time. How do we take advantage of them? Broadly, we want to look for situations where the compiler gets very strict. For example, most compilers don’t care if an “if” statement is exhaustive, but will carefully check “switch” statements for any missing cases. If a user is trying to add or edit a case, they’re safer if all the previous conditionals were exhaustive switches. The moment they change the cases, the compiler will flag all the conditionals they need to reexamine.

Another common readability problem is using primitives in conditionals. Especially when an application parses JSON, it’s tempting to write lots of if-statements around string or integer equality. Not only does this open the door for misspellings, but it also makes it challenging for users to know which values are possible. There’s a big difference between having to check the edge cases when every string is possible and checking the edge cases when two-three discrete cases are possible. Even if primitives are captured in constants, the user is one impending deadline away from assigning an arbitrary value. If we use custom objects or enums, the compiler blocks invalid arguments and provides a clear list of valid ones.

Similarly, prefer a single enum over multiple bool flags if some flag combinations are invalid. For example, imagine a song that can be buffering, fully loaded, or playing. If we represent that as two bool flags, **`(loaded, playing)`**, the compiler permits the invalid input **`(loaded: false, playing: true)`**. However, if we use an enum, **`.buffering`/`.loaded`/`.playing`**, the invalid state is not even possible. “Disable invalid combinations of settings” would be a basic feature in a customer-facing UI. But when we’re writing the code inside the app, we often forget to grant ourselves the same protection.

![](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/86c6e4cd-a94f-40f3-922a-f6092fa7b68b/1g-HfEsjlYSYc6gyLvBsSlQ.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=ASIAT73L2G45GOCUNFG2%2F20190817%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20190817T162941Z&X-Amz-Expires=86400&X-Amz-Security-Token=AgoJb3JpZ2luX2VjEMX%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJGMEQCIDy9NW1Wlely5J6%2Fv9Ac3waSu3SeksFsQIzUX3u6bduoAiBeq1KtmQaL%2Bg%2B5zfhPuk3WNKmw5xvBh%2FOA6eydx01DtiraAwheEAAaDDI3NDU2NzE0OTM3MCIMKAm0P8mzKGdYUPr1KrcDytPY1UroIsNB4VSXYlbM5Yw0Vh2S%2FEJnD2bV%2FaMGOy9y3dNC%2FgmvipEzZoiOlq%2B%2B%2FdX6tCqfjHOLkpaK03orcCue9nGmyhaj9467xbolDI73khSQoTO3G6uTfneYn9TcwcpmCI9NpxIkpdPGB78LXFlXkM5Cb2oL39IBs39y4oKZcwipdUfvfrbyHML%2Blcebmga0IBFbrEe3Vhru52TTf8%2BoLjSKT9YucWIUllyjqY57dM4PirwQ1svD9wmfhTPUuuKHmk50foNRAJGYFNogA6hECoSPXXFO5KEaiHd2Pz7uF1uPK0ZZyDJ1KjnWLr19gMiAdsVqVPhfWdHMon2M3bzjKHtuZ5azlpHw%2FkxWrSUEK4plFoOwCu8Gd0Cy5vxxqJleqCY1CDurKMIYKVJyv4W2hTDIJp1glmq2d4sqOoeZGm5Qm9XaqDyOkHqKlgvZHnNhfz3uBmkeCOHvK1Qxf0c3zUzhhT2MJfbqTVamv%2FSK8RwcZc%2BjAknY4HntfeMCXYVVzHsti5StjYU5nTrpxwWuEnbun9kx7lxUfiX%2FzwMQuHbsCzUw2aOAmEa9cjQRQZI%2FrfwTAjCE9N%2FqBTq1AULN%2B8RC%2FEhox%2BpsC0JERquika47A2GhabnZHMuhQAPS3YTKN1vAd53uVvVPLiEGBJpCK1u382DaqlUWSQwuOKFd2wfTsE5erRor9iiSuROTRabvYIxmG5%2FmBjG27DOJLimrR%2FDesre1F0Kx9ja0rytdkaQoCpTHvJNUuLb9bnrly1mOIqDgUFPUIoGBG3hHeJDKGlnbXhMSl5connezeXfpeDdcMt3kO4sUfTArefdW5iENY%2Bc%3D&X-Amz-Signature=1b58095c969839b0421b35653f7c6b41d11dd050637a605a1e659534b0a1b478&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D"1g-HfEsjlYSYc6gyLvBsSlQ.png")

![](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/c1b8a31d-8c1d-4d90-b946-a4c4834280ac/1TXVodVsYnRmHbax9QUJrMA.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=ASIAT73L2G45J7RQZPU2%2F20190817%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20190817T162959Z&X-Amz-Expires=86400&X-Amz-Security-Token=AgoJb3JpZ2luX2VjEMX%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLXdlc3QtMiJIMEYCIQCNSreERqxgM7btQVvL5uvR9tfRrx%2BZMHRY0gnpVpNr0gIhAPFyKq%2BTtjdrHfHujmF08ok69RWfJAdHSjSVeepF4IndKtoDCF4QABoMMjc0NTY3MTQ5MzcwIgys6leKDUVQMsL%2FC3sqtwOSAwCN6JDlEqGjwuIGsgznaLaxK3NvDcJymaX80GEWz5CW44DAofBJBseRDK3lf%2BDcOgcgOnEYcmoO4kT6zQpayaOZjJOiBptHusY4Gih6M2Om3In7UKdiHSm6IvEwEBMF3vcjnooF4A5k5O8FrF3S7HWru%2BejiTIsKSr%2FstlzGoXhdlJSjhyKnH%2FMbEtiqPPZ2zgaEZd%2BzaoizbazIJKZYoMcpmRtzpvcRo7e7xDLsKwThORFwaEE3mJ0ZNJqqLAUlHQj19ejywKD0sxa5l3zHgiMZnkR0kjXzG3pTAu7CzB5Q%2FUqs3HL%2F7HxLafPRWTiCCj9w%2FO6io5nZzxT4LpXm%2FxMm3te9BtI7bwstfD%2B1LklOaofeb1mmL704hpBqkeVduuY9ep1GdFNKSSXpbL3W%2FgcOFNOgpN02DKid3%2BqCoAc3fcxhHrGP0Yq0YuowThYFD3rd2AfH2ftxt%2FrmBgz%2FI1IgBkxGYt7Hozti%2F5XWWOMYOr1v16%2FFxXfHz2sCj9JEV9nWLkVpWg%2BDUWfXZSplB51cKdlRzWX9Ouk%2BC6PCrBbbQrsuW6OTHF6FR7TnTx0gseTYYrGMOXl3%2BoFOrMBbnVIG0TX6GYrthA9wtxzZLc%2BwhK88l%2FZx5Q1LqW2gRw58fGfeCTeSKJCyZ57ksBBIb9qQsGQMlGmSRbTZhnkte%2FSgN5Wt3lOJbMOCptMANfnD9VCDVY1wbqHfkwLRuycUBhQNp%2BDpuXuE3aMiT2ipWGxkYnLrUgUVKOabX9kZobKmRYa8r18yzzboaqZnnLG1vJqXMU2%2FIln6aTdj5p7lb6PUe1Tu%2FrpfPo8r%2BszuLckp90%3D&X-Amz-Signature=0f57215adf8a26cd79ffb914ebc1193185cf79da41c03aecd04ae3b33d18e361&X-Amz-SignedHeaders=host&response-content-disposition=filename%20%3D"1TXVodVsYnRmHbax9QUJrMA.png")

Invalid combinations are disabled before interaction; customers don’t have to think about which configurations are inconsistent. Screenshot: Apple

Over the course of this user flow, we’ve arrived at the same rules we had at the start. But now we have a process for generating and customizing them. We ask ourselves:

- Will this code be easy for users to find? Will it clutter search results for unrelated features?
- Once found, can the user quickly confirm the code’s current behavior?
- Can users lean on machine validation to edit or reuse this code safely?

In short, readable code must be usable. And maybe, as a side effect, it’ll look pretty too.

---

**Footnote1** "."Booleans may feel more reusable, but reusability implies interchangeability. Imagine two flags, `tappable` and `cached`. They represent concepts on completely different axes. But if both flags are boolean, we can casually swap between them, sneaking non-trivial statements (“caching is related to tappability”) into a tiny line of code. With enums, we’re forced to create explicit, testable “unit conversion” logic whenever we want to form this kind of relationship.
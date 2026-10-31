---
layout: post
title: "Inception (Of Sorts)"
date: 2025-05-29
tags: [pharmacy, technology]
author: Pharmacist Daz
---

AI is the current panacea of all humanities woes. The claims (and some of the hype cycle claims) are in the headlines nearly every day, and this seems especially so within the healthcare sphere.

I'm certainly not a Luddite, but perhaps I'm not so assured that adding AI to anything and everything will solve problems, but I am sure that AI has a place, and will continue to develop at pace. One of my favourite quotes about technology is attributed to Roy Amara, a Stanford computer scientist in the 1960s (so I am told).

> We overestimate the impact of technology in the short-term and underestimate the effect in the long run

So I do think it is important for healthcare teams to have an understanding of the "flavours" of AI, and their benefits and their fallibilities (bias, hallucinations, drift). I am a life-long member of the Royal Pharmaceutical Society, and am pleased to support them in promoting their approach to AI in Pharmacy.

I do consider a key skill for the future will be "Prompt Engineering" to maximise the efficiency and accuracy of the outputs of various Large Language Models (LLMs). Just Google the term, and you will identify a number of frameworks for structuring any prompt to a LLM (PICKSIE is a model promoted by a government department, and they even developed a web application to walk a user through the prompt generation).

I saw an image on LinkedIn which suggested a framework for the prompt structure, and this is where my "Inception" approach started. I decided to feed the image into ChatGPT and then added the following prompt:

> You are an expert prompt engineer for various LLMs. You are aware of the variety of models available and their particular requirements to meet a users objectives. Using an analysis of the image, use the structure to build a suitable prompt for a LLM to support users on getting a response from a LLM that is optimal and accurate. Structure the prompt so that the LLM operates in a question and answer approach, to gather information from the user to eventually produce the required output. Document your prompt with information for a user to understand the approach of the prompt.

ChatGPT responded very cordially and provided the following code, that can be used in any LLM to help support a user through the generation of a prompt for the task in hand:

---

You are an expert LLM prompt builder. Please ask me a short series of questions to help generate the best possible prompt for my needs. Follow the structure below:

**Step 1 — Context**
Ask me: "What task or situation are you working on? Briefly describe your background or the purpose of this request."

**Step 2 — Role**
Ask me: "What kind of expert should the AI pretend to be? (e.g., software engineer, travel copywriter, clinical researcher)"

**Step 3 — Action**
Ask me: "What do you want the AI to do exactly? Be specific about what kind of response you're looking for."

**Step 4 — Format**
Ask me: "How should the output be presented? (e.g., bullet points, paragraphs, table, step-by-step list, code snippet)"

**Step 5 — Tone**
Ask me: "What tone or mood should the response have? (e.g., formal, friendly, witty, persuasive, academic)"

After asking and receiving all 5 answers, write a complete, high-quality prompt that includes:

- Clear context
- Assigned expert role
- Action requested
- Output formatting style
- Tone guidance

Wrap the prompt in triple quotes (""") for clarity. Also provide the user a title for the prompt and a short note explaining how to use or reuse it.

---

I've used the above in other LLMs such as Claude — and it works reasonably well in structuring my ideas and needs for my ask of the AI.

I think it is this level of understanding of how to get the best out of these new tools that will be key for teams. I am no expert, and class myself as an enthusiastic beginner — so you might be able to suggest improvements in my approach, or even the prompt. Please do comment.

---
layout: post
title: Preparing for the Google Cloud Professional Network Engineer certification
subtitle: "This blog equips you with the knowledge and tools to tackle Google Cloud's Professional Cloud Network Engineer certification. Dive into exam essentials: Understand key skills tested and Google's expectations.
Your study plan: Discover best practices, recommended resources, and practice tips. Insider knowledge: Gain insights on exam format, structure, and potential challenges. My experience: Learn from my journey and benefit from valuable advice I have gleaned after achieving this certification three times."
#description: ""
#cover-img: /assets/img/path.jpg
thumbnail-img: /assets/img/pcne/googlecloudprofessionalcloudnetworkengineerbadge.png
share-img: /assets/img/pcne/googlecloudprofessionalcloudnetworkengineerbadge.png
readtime: true
share-title: "How to prepare for the Google Cloud Professional Cloud Network Engineer certification"
share-description: "In this blog I cover Google Cloud’s Professional Cloud Network Engineer certification and offer my advice and guidance after certifying three times over the past four year on preparing to become a Google Cloud Professional Cloud Network Engineer."
share-img: /assets/img/pcne/googlecloudprofessionalcloudnetworkengineerbadge.png
tags: [Google Cloud Professional Cloud Network Engineer, PCNE, Certification, Exam, Guidance]
---

Last week I embarked upon my latest certification renewal- Google Cloud Professional Cloud Network Engineer (PCNE). This was my third time certifying as a Professional Cloud Network Engineer having initially passed in January 2020, renewed in 2022, and again in 2024. The exam had been updated this time, so it was good to see newer content included in some of the questions, and for anyone wondering if the updated exam is still as difficult as its predecessor: it is, if not tougher! 

As a Google Cloud Professional with nine certifications under my belt and aiming for my tenth (Professional Machine Learning Engineer pending…), I thought I’d write this blog to share my experience, exam tips, thoughts, preparation, and general guidance to help others planning to take this exam.

* toc
{:toc}

# What is the Google Cloud Professional Cloud Network Engineer certification?

Google Cloud's Professional Cloud Network Engineer (PCNE) is one of Google's most challenging professional certifications. Google Cloud's Professional certifications are role-based certifications to measure an individual’s proficiency at performing a specific role using Google Cloud technology. As per [Google's definition:](https://cloud.google.com/learn/certification/cloud-network-engineer) 

A Professional Cloud Network Engineer implements and manages network architectures in Google Cloud. This individual may work on networking or cloud teams with architects who design cloud infrastructure. The Cloud Network Engineer uses the Google Cloud Console and/or command line interface, and leverages experience with network services, application and container networking, hybrid and multi-cloud connectivity, implementing VPCs, and security for established network architectures to ensure successful cloud implementations.

The Professional Cloud Network Engineer exam assesses your ability to:

- Design, plan, and prototype a Google Cloud network
- Implement Virtual Private Cloud (VPC) instances
- Configure network services
- Implement hybrid interconnectivity
- Manage, monitor, and optimize network operations

![Google Cloud Professional Cloud Network Engineer Badge](/assets/img/pcne/googlecloudprofessionalcloudnetworkengineer.png "Google Cloud Professional Cloud Network Engineer Badge")

*Google Cloud Professional Cloud Network Engineer Badge*

# Who is the Google Cloud Professional Cloud Network Engineer certification aimed at?

The Google Cloud Professional Cloud Network Engineer certification is a specialist Professional level certification. I would recommend those new to Google Cloud certifications initially start with the following certifications before targeting the specialist certifications:
1.	Google Cloud Digital Lead (CDL)
2.	Google Cloud Associate Cloud Engineer (ACE)
3.	Google Cloud Professional Cloud Architect
These certifications provide a good foundation to help you progress to the more specialist Professional certifications.
# How difficult is the Google Cloud Professional Cloud Network Engineer certification?

Google Cloud has 3 levels of certifications starting at the entry level with Cloud Digital Leader, Associate Cloud Engineer, and a range of Professional level specialist certifications. 

All Google Cloud Professional certifications are challenging but the PCNE is one of the most challenging Professional certifications. The certification tests your in depth knowledge of all things networking within Google Cloud and Google Kubernetes Engine. This is a much narrower scope than the PCA, and therefore the contents is much more specialised and focussed entirely on GCP networking. If you are attempting PCNE after PCA, be prepared for a shock as the level of difficulty between PCA and PCNE is significant.

# How to prepare for and pass the Google Cloud Professional Cloud Network Engineer exam

Below are my recommendations on how best to prepare for the Professional Cloud Network Engineer exam based on my experiences with this and other GCP certifications.

# Exam Guide: Your North Star in the Cloud
{:.no_toc}

Having heard musings about the exam being recently updated, and seeing various comments it was now tougher than ever, I made sure I thoroughly reviewed all the content on the exam guide. Frustratingly Google doesn’t publish deltas or historical versions, so it wasn’t easy to identify exactly what was new in this release vs previous releases. That being said, certain elements were clearly new as they haven't been GA for particularly long times e.g. firewall insights and hierarchical firewall policies. 
As for all exams, my first piece of advice is to review the [Google Cloud Professional Cloud Network Engineer exam guide](https://cloud.google.com/learn/certification/guides/cloud-network-engineer) to get an understanding of the topics in scope of the exam, and assess how confident you feel with each topic. This baseline then enables you to target your training on areas you feel weakest in.

The exam guide breaks down exam content into five sections, providing a weighted percentage for each. These sections are:

-	Section 1: Designing, planning, and prototyping a Google Cloud network (~26% of the exam)
-	Section 2: Implementing Virtual Private Cloud (VPC) instances (~21% of the exam)
-	Section 3: Configuring network services (~23% of the exam)
-	Section 4: Implementing hybrid interconnectivity (~14% of the exam)
-	Section 5: Managing, monitoring, and optimizing network operations (~16% of the exam)

Whilst I clearly got questions across all of these sections, it felt like a large portion of the exam focussed heavily on section 4: implementing hybrid interconnectivity. I had a lot of questions related to:

-	High availability VPN configuration, performance and best practice.
-	Dynamic routing, route-based routing and policy-based routing.
-	Dedicated and partner interconnect connections and VLAN attachments.
-	Cloud Router- BGP peering, route priority, MED, custom routes.

These areas are not my daily grind. My present role as a Google Cloud Architect is more typically involved in app modernisation and data migrations for large enterprise organisations, so I don’t get involved day to day in deploying and configuring network connectivity with Cloud VPN, Cloud Routers and interconnects. However, I recalled these topics being a key area in previous versions of this exam, and so I spent a lot of my preparation reading Google Cloud docs on each of these areas. Any whitepapers, blogs, best practices I could find on the topic I read! This definitely paid off as a lot of the exam focussed on them, and some questions specifically required knowledge of the performance of each solution, how and when to scale out for increased performance and what Google recommended best practices are for each.

It's also essential you understand how BGP routing works, and what alternative options exist if you have legacy infrastructure that doesn’t support BGP.

I’d also suggest focusing on VPC architecture options- understanding when to use standalone vs shared VPC, regional vs multi regional VPCs, peering, routing, and connecting to managed services like Cloud SQL.

The exam also covers Google Kubernetes Engine networking requirements, so understanding Kubernetes networking, cluster modes, subnet sizes, master authorised network access to the control plane and how these are configured are essential if you don’t have much day-to-day experience working with GKE.

From a security perspective, you need to:

- Understand how VPC service controls can help strengthen your overall security posture.
- Understand how Cloud Armour can provide protection against DDoS attacks and other threats.
- Leverage private Google access to avoid routing traffic over the internet.
- Configure Cloud DNS, knowing when to use Private zones vs Public zones and how to forward back to on premise DNS servers.
- Understand the added security benefits of DNSSEC and how it can be enabled.
- Grasp the distinct roles of traditional VPC firewall rules and hierarchical firewall policies.
- Identify what firewall rules take priority over others, and how to enable logging.

You will also need to delve into the intricacies of Google Cloud's Load Balancing options from External TCP/UDP Network Load Balancers, Internal TCP/UDP Load Balancers, External HTTP(S) Load Balancers, to Internal HTTP(S) Load Balancers and ensuring you select the optimal solution for your application's requirements. The exam also validates your understanding of configuring these load balancers including how to perform health checks, configuring firewall rules to permit the required flows and configuring backend services that effectively scale.

# Recommended training material and courses for Google Cloud Professional Cloud Network Engineer certification including practice exam question sources.

- Google Cloud Skills Boost learning path Preparing for Your Professional Cloud Network Engineer Journey
- Google Cloud Documentation
- Google Cloud Solutions
- Priyanka Vergadia aka The Cloud Girl

## Google Cloud Skills Boost Learning Path: Preparing for Your Professional Cloud Network Engineer Journey
[Google Cloud Skills Boost Network Engineer Learning Path]( https://www.cloudskillsboost.google/paths/14) is an online self-paced training course. The content is presented in a series of thirteen courses covering the areas included within the exam guide, and a series of Quests providing lab scenarios for you to practice and gain hands-on experience. Each course has several modules consisting of a series of videos, labs and an end of module quiz to assess your understanding of the content covered. 

The platform also enables you to play the videos at a faster speed, enabling you to reduce the time to complete the course and speed through areas you are already familiar with.

## Google Cloud Documentation
I'm a big fan of [Google Cloud Documentation](https://cloud.google.com/docs). There are documentation pages for each Google product, providing overviews, getting started guides, code samples, and the Cloud Architecture Framework and Cloud Architecture Center for further guidance and best practices. Reading the associated product documentation pages after completing training courses helps to further embed your knowledge and clarify any points you may still be struggling with.

On this occasion, my main revision was based on the topics listed within the exam guide, and reviewing the relevant Google Cloud docs for the topics I felt I needed to brush up on. 

## Google Cloud Solutions
[Google Cloud Solutions](https://cloud.google.com/docs/tutorials) provides a vast range of QuickStart’s and tutorials to guide you through, and provide hands on experience with Google Cloud's products and services. These tutorials prove invaluable providing additional experience working with some of the services you may be less familiar with.

## Priyanka Vergadia aka The Cloud Girl

For those who benefit more from visual learning- Priyanka Vergadia aka The Cloud Girl has created an excellent collection of [sketchnotes](https://thecloudgirl.dev/sketchnote.html) covering a wide range of Google Cloud products, services, and concepts in an easy to digest format.

![Example sketchnote for Google Cloud Load Balancing options from Priyanka Vergadia](/assets/img/pcne/sketchnoteloadbalanceroptions.jpg "Example sketchnote for Google Cloud Load Balancer options from Priyanka Vergadia")

*Example sketchnote for Google Cloud Load Balancer Options from [Priyanka Vergadia]( https://thecloudgirl.dev/CLB.html)* 

The sketchnotes have been released as a book titled [Visualising Google Cloud](https://thecloudgirl.dev) which is a handy reference for getting to grips with Google Cloud's products and concepts for the Professional Cloud Architect and subsequent associate and professional exams. It is also a handy reference to have for day-to-day use as you are learning more about Google Cloud’s offerings.

Priyanka regularly posts videos on her social media channels including various [Cloud Bytes](https://youtube.com/playlist?list=PLIivdWyY5sqIQ4_5PwyyXZVdsXr3wYhip)  videos covering Google Cloud products in under a minute, and has her own blogs on [Medium](https://pvergadia.medium.com).

## Review the exam guide (yes, again!)
{:.no_toc}

Once you have completed all the training materials, review the exam guide again. This time you should feel more confident in your level of knowledge for each topic. If there are still topics in the guide you don't feel comfortable with, spend more time focussing on these, revisiting the content in the training courses, or researching the content in Google docs, and YouTube videos etc.

# Take the Google Cloud Professional Cloud Network Engineer practice exam
{:.no_toc}

Once you are feeling confident you understand all the concepts covered in the exam guide, it's time to do a practice test. Google provides a [free practice test](https://docs.google.com/forms/d/e/1FAIpQLServ0tNGkr-dYAfmez_Gdk74dmVypZjzUKrkVFtFcArzhmPow/viewform) consisting of 15-20 questions to mimic the type of question you may see on the exam. 

Complete the practice exam as a closed book exam- don’t allow yourself to search for answers, or review study material prior to answering. It’s key to see how well you are performing and highlight areas of weakness you may need to improve prior to booking the real exam.

At the end of the practice exam, review all the questions including those you have got right and read the feedback provided by Google for each answer. This feedback clarifies why a particular answer is correct, and why others are incorrect, further consolidating your understanding of the subject. For any answers you are still unclear about, or if you feel the feedback doesn’t help you to understand why a particular answer is correct, spend more time revisiting the associated topic on one of the available training platforms or YouTube videos.

# Google Cloud Professional Cloud Network Engineer Exam Strategy and Tips

Perform the first iteration of the exam quickly, answering the questions you are confident you know the answer for. If you don’t know the answer to a question, mark it for review at the end and try to rule out any incorrect answers from those available. Typically, there are a couple of answers that may be correct, however a subtle word within the question usually makes one of the answers a better fit than the others.

Once you complete your first iteration, review your marked questions, and spend more time on them accordingly. By taking this approach you can determine how long you can spend your remaining time on these tougher questions as you know how many you marked for review. You may also get lucky and find a later question on the exam helps you to identify the answer to a previous question you were unsure on either directly or indirectly by triggering a memory of some detail that earlier escaped you!

Upon completion of the exam, a provisional pass or fail is displayed on the screen. Look out for it, if it’s your first Google Cloud certification you can quite easily miss it as for whatever reason, it's not highlighted particularly well! Google subsequently confirms the pass/failure within 7-10 days' time (although it's often sooner!).

# How to book the Google Cloud Professional Network Engineer exam
{:.no_toc}

The Google Cloud Professional Cloud Network Engineer exam can be booked via Kryterion test centres on the [webassessor website](https://www.webassessor.com/googlecloud/). The exam can be taken in a test centre, or via a remote proctored exam monitored via a web camera and microphone.

![Kryterion logo](/assets/img/cdl/kryterionlogo.png "Kryterion logo")

*Kryterion Test Centres Logo*

Since covid I have been taking advantage of the remote proctored exams for convenience. The nearest test centre to me was around 1 hour away. There are a various [system requirements](https://kryterion.force.com/support/s/article/Online-Testing-Requirements?language=en_US) for online proctoring. This includes installing a secure browser application, and disabling various components that may interfere with the remote proctoring such as firewalls, anti-virus, pop up blockers etc. For this reason, Kryterion recommends you use a personal device for the exam. There is a system checker available to test internet speed, microphone, and webcam functionality [here](https://www.kryterion.com/systemcheck/).

Kryterion requires you to enrol in biometrics and create a biometrics profile which is used to identify yourself digitally based on facial characteristics. Each time you launch an exam, a biometric check is performed to validate you match your biometric profile. You can launch the remote proctored exam 10 minutes before your scheduled exam time. However, during busy times you may find you are waiting around for up to 30 minutes for a proctor to join and ‘secure the testing environment.’ This consists of displaying your government issued ID to the proctor, and then providing a 360-degree view of the room, and your clear desk to the proctor.

Once they are happy the room is secure, your exam is started. The proctor monitors you via the webcam and microphone and will pause the exam if there are any issues and contact you via the secure browser chat functionality. This has happened to me once when the proctor advised my video stream had stopped working mid-exam. The exam was paused whilst my laptop restarted, and the proctor verified the stream was working again. 

On a second occasion, the proctor advised my video stream wasn't working before the exam had started- a reboot failed to resolve the issue and I was advised to contact Kryterion support. This wasn't the greatest start to the exam, as I was now past my scheduled start time, however support were able to reschedule the exam to begin as soon a i had finished troubleshooting the issue with them, or I could book it for another day if it was no longer convenient.

It is best to book your exam ahead of time, as this gives you a date to work towards completing study and revision and helps ensure you get to choose a date/time that suits you best. If you leave booking the exam until after you finish your studying, you may find there aren’t as many convenient times available as you would like. If you find yourself in this position, check back regularly as I've seen a lot of times that were not available when checking the previous day, become available a day or two later. Provided you give at least 24 hours' notice, you are free to reschedule your exam to another time if for any reason you are not ready.

# How long is the Google Cloud Professional Cloud Network Engineer exam?
{:.no_toc}

The Professional Cloud Network Engineer exam is a two-hour exam during which you will need to answer 50-60 multiple choice and multiple select questions. 
I find for many of the professional certifications, I typically complete my first pass of the answers within an hour, however on the latest Professional Cloud Network Engineer exam I recall being 50% through the exam and having hit the one-hour mark. This got me rather worried that I wouldn't have time to review my questions and potentially may need to rush answering some of the later questions! Fortunately, the second half of questions were shorter and/or quicker for me to answer leaving me with 15 minutes to review and revisit any questions I was unsure on.

# How long is the Google Cloud Professional Cloud Network Engineer certification valid?
{:.no_toc}

All Google Cloud Professional certifications are valid for 2 years. You can recertify 60 days prior to certification expiration.

# How much does the Google Cloud Professional Cloud Network Engineer exam cost?
{:.no_toc}

The Google Cloud Professional Cloud Network Engineer exam costs $200 USD.

Thanks for taking the time to read this blog, I hope you find it useful in preparing for the Google Cloud Professional Cloud Network Engineer certification. Please feel free to share, [subscribe](https://www.cloudbabble.co.uk/subscribe) to be alerted to future posts, follow me on [LinkedIn](https://linkedin.com/in/jamiethompson85), and react/comment below! 

If you're new to Google Cloud certifications, or you're deciding what certification to do next, check out my other blog posts covering:

- [Google Cloud Professional Cloud Architect Certification](https://www.cloudbabble.co.uk/2023-02-28-Google-Cloud-Professional-Cloud-Architect/)
- [Google Cloud Digital Leader Certification](https://www.cloudbabble.co.uk/2022-12-06-GoogleCloudDigitalLeaderCertification/)

Do reach out if you would like me to cover any particular areas of Google Cloud products, concepts or certifications in future posts.

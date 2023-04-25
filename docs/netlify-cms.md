# Netlify CMS

*Jekflix* is ready for Netlify CMS integration, which means you can create/edit posts, authors, categories, theme, etc... without touching a line of code!

However, you **can only use this if you're cloning the repo**. In the case you're using the `gem`, you'll need to setup Netlify CMS in your project by yourself.

## Deploy with Netlify

Use the Netlify [documentation](https://www.netlify.com/docs/continuous-deployment/) to set up *Continuous Deployment*.

When setting the **Build command**, change it to `gulp build`. If you deployed your site already and forgot to do that, follow the steps below:

1. Go to the top menu and select **Deploys**
1. In **Continuous Deployment > Build Settings**, click on **Edit settings**
1. Change the **Build command** to `gulp build`

That's it. Every time you push a new commit, your project will build and deploy.

## Integrate with Netlify CMS

Once you have deployed your website with Netlify successfully, follow the [Enable Identity and Git Gateway](https://www.netlifycms.org/docs/add-to-your-site/#enable-identity-and-git-gateway) walkthrough to be able to access your website CMS.

Some important things to keep in mind:

1. Access your CMS locally through `localhost:3000/admin` or `yourdomain.com/admin`
1. The available CMS data is **always** pulled in from your repo. Which means, even if you are working locally, the CMS won't get local changes till you push them into GitHub.
1. Every change *published* through CMS will be automatically deployed to production, so be careful with what you publish.
1. The CMS allows you to save data as *draft* though, so it won't go to production till you publish the changes 🙂

See some CMS screenshots:

![Netlify CMS post list screenshot](https://res.cloudinary.com/dm7h7e8xj/image/upload/v1566479287/netlify-page-1_a0qezm.jpg)

![Netlify CMS post edition screenshot](https://res.cloudinary.com/dm7h7e8xj/image/upload/v1566479287/netlify-page-2_aupygb.jpg)

![Netlify CMS workflow screenshot](https://res.cloudinary.com/dm7h7e8xj/image/upload/v1566479287/netlify-page-3_bj5sks.jpg)

![Netlify CMS site settings screenshot](https://res.cloudinary.com/dm7h7e8xj/image/upload/v1566479287/netlify-page-4_ycfqdp.jpg)

![Netlify CMS theme settings screenshot](https://res.cloudinary.com/dm7h7e8xj/image/upload/v1566479287/netlify-page-5_k6dan9.jpg)
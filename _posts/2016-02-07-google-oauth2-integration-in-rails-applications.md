---
layout: post
title:  "Google OAuth2 OmniAuth"
subtitle: Excerpt from Soulshaping by Jeff Brown
bigimg: ![Google](/img/google.png) ![Google+](/img/plus.png) ![OAuth](/img/oauth.png)
date:   2016-02-07 16:47:14 +0530
categories: ruby_on_rails
---
![Google](/img/google.png) ![Google+](/img/plus.png) ![OAuth](/img/oauth.png)

The overall idea behind this first post is to help you setup Google OAuth2 authentication in your Ruby on Rails application. Any kind of OAuth provides an easy and a secure way to sign up to an application on the internet.

Firstly, let's understand the meaning of OAuth.

As Wikipedia quotes `OAuth is an open standard for authorization, commonly used as a way for Internet users to log into third party websites using their Microsoft, Google, Facebook or Twitter accounts without exposing their password.`

Now, let's implement OAuth2 in a Ruby on Rails application.

1. Add `omniauth` and `omniauth-google-oauth2` ruby gems to your `Gemfile`.

2. Next, you need to get your `client_id` and `client_secret`, inorder to get these you need to register your application with google to get access to their `google+` API. 

	- `Set up your Google Project`
		- Visit [Google Console][google-console] to register your application with google. 
		- Click on `Create a new project` and fill up the empty input text fields with necessary data.
		![Google New Project](/img/project.png)
		- Choose `Google+` API and enable it.
		![Google+ API](/img/google_api.png)
		- Then, set up the credentials.
		![Credentails](/img/credentials.png)
		- Enter your Origin URL and Callback URL, like shown below
		![Credentials 2](/img/credentials_2.png)
		- Once, everything is correctly set up, you can download the `client_id` and `client_secret` as a JSON file.
		- Now, you just have to make changes in your application to complete the entire process.

3. In your text editor open `config/initializers/devise.rb` and add the following line of code.

		config.omniauth :google_oauth2, "GOOGLE_CLIENT_ID", "GOOGLE_CLIENT_SECRET, { }
4. Replace `GOOGLE_CLIENT_ID` and `GOOGLE_CLIENT_SECRET` with the secret id from the downloaded JSON file.

5. Add the following devise route in `config/routes.rb`, so the callback routes are defined.

		devise_for :users, :controllers => { :omniauth_callbacks => "users/omniauth_callbacks" }

6. Make your model omniauthable, If the model name in your application is `User`, then open `/app/models/user.rb`, else open `/app/models/YOUR_MODEL_NAME`, where `YOUR_MODEL_NAME` is something else.

		devise :omniauthable, :omniauth_providers => [:google_oauth2]

7. Create a new folder in `app/controllers` named `users` and in `users` create a new file `omniauth_callbacks_controller.rb` and insert the code shown below in the file created.

		class Users::OmniauthCallbacksController < Devise::OmniauthCallbacksController
		  def google_oauth2
		      # You need to implement the method below in your model (e.g. app/models/user.rb)
		      @user = User.from_omniauth(request.env["omniauth.auth"])

		      if @user.persisted?
		        flash[:notice] = I18n.t "devise.omniauth_callbacks.success", :kind => "Google"
		        sign_in_and_redirect @user, :event => :authentication
		      else
		        session["devise.google_data"] = request.env["omniauth.auth"]
		        redirect_to new_user_registration_url
		      end
		  end
		end

8. Next, open `app/models/user.rb` and insert the code shown below.

		def self.from_omniauth(access_token)
		    data = access_token.info
		    user = User.where(:email => data["email"]).first

		    # Uncomment the section below if you want users to be created if they don't exist
		    # unless user
		    #     user = User.create(name: data["name"],
		    #        email: data["email"],
		    #        password: Devise.friendly_token[0,20]
		    #     )
		    # end
		    user
		end

9. Finally, add the Google authentication link to your Sign Up or Sign In page. The code shown below is in `.erb` format.

		<%= link_to "Sign in with Google", user_omniauth_authorize_path(:google_oauth2) %>

10. That's it, you have finally added Google authentication to your Ruby on Rails application and you can tweak it incase you need additional data of the user.

[google-console]: https://console.developers.google.com/apis

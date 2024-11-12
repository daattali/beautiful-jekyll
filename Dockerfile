# Utiliser l'image officielle de Ruby comme base
FROM ruby:3.1

# Installer les dépendances pour Jekyll et le serveur
RUN apt-get update && apt-get install -y \
  build-essential \
  libssl-dev \
  libreadline-dev \
  zlib1g-dev \
  libsqlite3-dev \
  sqlite3 \
  nodejs \
  && rm -rf /var/lib/apt/lists/*

# Définir le répertoire de travail
WORKDIR /usr/src/app

# Copier les fichiers de votre projet dans le conteneur
COPY . .

# Installer les gems nécessaires
RUN gem install bundler && bundle install

# Exposer le port 4000 pour accéder à Jekyll
EXPOSE 4000

# Commande pour démarrer le serveur Jekyll
CMD ["bundle", "exec", "jekyll", "serve", "--host", "0.0.0.0"]

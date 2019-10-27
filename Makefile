
build: ## Build image for development
	docker build -t blog .

run: ## Run docker with volume mount
	docker run --rm -p 4000:4000 --name blog -v "$PWD":/srv/jekyll blog
	
help: ## Display this help. Default target
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "};
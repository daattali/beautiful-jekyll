
## Anatomy of Natural Language Processing

As Wikipedia says 'Natural language processing (NLP) is a field of computer science, artificial intelligence, and computational linguistics concerned with the interactions between computers and human (natural) languages and, in particular, concerned with programming computers to fruitfully process large natural language corpora'.


### Why is NLP required?

There are several reasons that made NLP popular within the Artificial Intelligence and Machine Learning community, especially the huge opportunity that NLP provided to everyone to work on large sets of textual data.

Few of the domains, where NLP plays a crucial role is:

* Auto Summarization
* Chatbots
* Machine Translation
* Text Classification
* Sentimental Analysis
* Speech Recognition

### Steps taken to solve a NLP problem

In this notebook, let's try to classify news's articles to different categories based on the article content and in doing so let's look at the various steps that we take to solve a NLP problem.

#### 1. Collection of the Dataset

The first and foremost step in any Machine Learning or NLP based problem is to collect a dataset. For our problem, let's try to collect news articles from [Doxydonkey](http://www.doxydonkey.blogspot.in).



```python
# imports
import urllib2
from bs4 import BeautifulSoup
```


```python
# URL to collect the data
url = "http://doxydonkey.blogspot.in"
```


```python
# Method to request, response and soup the data
def beautifySoup(url):
    request = urllib2.Request(url)
    response = urllib2.urlopen(request)
    soup = BeautifulSoup(response)
    return soup
```


```python
# Collecting all articles hyper links
def collectArticles(links):
    articles = []
    for link in links:
        content = []
        soup = beautifySoup(link)
        divs = soup.find_all('div', {'class': 'post-body'})
        for div in divs:
            content += map(lambda p: p.text.encode("ascii", errors="replace").replace("?", ""), div.find_all("li"))
        articles += content
    return articles
```


```python
# Method to collect all the articles data
def collectData(url, links):
    soup = beautifySoup(url)
    for a in soup.find_all("a"):
        try:
            title = a["title"]
            url = a["href"]
            if title == "Older Posts":
                links.append(url)
                collectData(url, links)
        except:
            url = ""
    return
```


```python
# global list that stores all the article hyper links
links = []
def collectParameters():
    links.append(url)
    collectData(url, links)
    print(len(links))
```


```python
# calling the parameters method 
collectParameters()
```

    80
    


```python
# articles list stores all the content
articles = collectArticles(links)
print(len(articles))
articles[0]
```

    2673
    




    'Airbnb raises $1 billion inlatestround of funding:Onlineroom rentingservice Airbnb Inc said on Thursday it had raised $1 billion in its latest round of funding, valuing the company at $31 billion.The company turned in a profit on an EBITDA basis in the second half of 2016 and expects to continue to be profitable this year, the source said, adding that Airbnb had no plans to go public anytime soon.The company is locked in an intensifying global battle with regulators who say the service takesaffordablehousing off the market and drives up rental prices.Airbnb raised $447.85 million as part of the funding, a source close to the company told Reuters. The company said in September it had raised about $555 million as part of the same round of funding.Airbnb, which operates in more than 65,000 cities, has enjoyed tremendous growth as it pushes ahead with its plansofglobal expansion.'



#### 2. Term Frequency - Inverse Document Frequency

TF-IDF weight is often used in information retrieval and text mining. The weight is a statistical measure used to evaluate how important a word is to a document in a collection or corpus.

TF-IDF is made up of two components: 
* TF - Term Frequency
        
        Term Frequency is the measure of how frequently a word appears in a document.
        TF(t) = (Number of times term t appears in a document) / (Total number of terms in the document)
        
* IDF - Inverse Document Frequency
        Inverse Document Frequency the measure of how important a term is.
        IDF(t) = log_e(Total number of documents / Number of documents with term t in it)


```python
# importing feature extractor TF-IDF vectorizer

from sklearn.feature_extraction.text import TfidfVectorizer
```


```python
# instantiating tfidf vectorizer
vectorizer = TfidfVectorizer(max_df=0.5, min_df=2, stop_words="english")
```


```python
# Applying tf-idf transformation on the articles 
articles_tfidf = vectorizer.fit_transform(articles)

# Let's see the tf-idf for the first article
print(articles_tfidf[0])
```

      (0, 4527)	0.093459986294
      (0, 880)	0.0909888475678
      (0, 9245)	0.125506358268
      (0, 5484)	0.0593929321553
      (0, 12111)	0.136331194112
      (0, 4293)	0.136331194112
      (0, 2522)	0.0853580208378
      (0, 1)	0.065168725165
      (0, 470)	0.109464227828
      (0, 8136)	0.103883585377
      (0, 427)	0.158782106766
      (0, 10394)	0.0896669240819
      (0, 9883)	0.0904124688247
      (0, 11941)	0.0768705699236
      (0, 2603)	0.0766677306981
      (0, 7515)	0.0847935427048
      (0, 539)	0.113991816532
      (0, 363)	0.169920689887
      (0, 8980)	0.0869161877993
      (0, 9696)	0.121217078597
      (0, 4015)	0.123688217323
      (0, 7265)	0.0517256017034
      (0, 10412)	0.0532921082588
      (0, 10199)	0.0728780620055
      (0, 9604)	0.100322272811
      :	:
      (0, 9194)	0.0657727820619
      (0, 8711)	0.0676923544855
      (0, 735)	0.0880771876065
      (0, 10875)	0.177538939725
      (0, 13072)	0.0378691826488
      (0, 9066)	0.0955164362715
      (0, 2980)	0.0875720285004
      (0, 4534)	0.102520325273
      (0, 180)	0.0853580208378
      (0, 5550)	0.0794643241154
      (0, 10304)	0.0705467582402
      (0, 1598)	0.100928007859
      (0, 4101)	0.133419534151
      (0, 9064)	0.0717214619913
      (0, 12206)	0.0983256447076
      (0, 277)	0.0884205814672
      (0, 12531)	0.120451910281
      (0, 10049)	0.14874067677
      (0, 6779)	0.0767689144505
      (0, 9353)	0.213261264741
      (0, 11862)	0.0730484148993
      (0, 5171)	0.298211234269
      (0, 1741)	0.127885890416
      (0, 9354)	0.0950423945693
      (0, 892)	0.545073115219
    

#### 3. Clustering the articles

Next, let's cluster the above articles in order to predict the category of future articles.

Let's use KMeans algorithm to cluster the articles. 


```python
# importing KMeans algorithm from sklearn
from sklearn.cluster import KMeans
```


```python
# instance of KMeans
km = KMeans(n_clusters=10, init='k-means++', n_init=2, max_iter=100, verbose=True)
```


```python
# fitting the model with the articles dataset
km.fit(articles_tfidf)
```

    Initialization complete
    Iteration  0, inertia 4766.061
    Iteration  1, inertia 2505.458
    Iteration  2, inertia 2486.992
    Iteration  3, inertia 2472.086
    Iteration  4, inertia 2466.478
    Iteration  5, inertia 2463.909
    Iteration  6, inertia 2461.882
    Iteration  7, inertia 2459.012
    Iteration  8, inertia 2454.963
    Iteration  9, inertia 2452.054
    Iteration 10, inertia 2451.220
    Iteration 11, inertia 2450.913
    Iteration 12, inertia 2450.580
    Iteration 13, inertia 2450.332
    Iteration 14, inertia 2450.119
    Iteration 15, inertia 2449.953
    Iteration 16, inertia 2449.779
    Iteration 17, inertia 2449.599
    Iteration 18, inertia 2449.449
    Iteration 19, inertia 2449.363
    Iteration 20, inertia 2449.310
    Iteration 21, inertia 2449.259
    Iteration 22, inertia 2449.234
    Iteration 23, inertia 2449.201
    Iteration 24, inertia 2449.181
    Iteration 25, inertia 2449.172
    Converged at iteration 25
    Initialization complete
    Iteration  0, inertia 4720.011
    Iteration  1, inertia 2477.708
    Iteration  2, inertia 2462.645
    Iteration  3, inertia 2456.979
    Iteration  4, inertia 2454.321
    Iteration  5, inertia 2453.198
    Iteration  6, inertia 2452.395
    Iteration  7, inertia 2451.989
    Iteration  8, inertia 2451.752
    Iteration  9, inertia 2451.645
    Iteration 10, inertia 2451.604
    Iteration 11, inertia 2451.591
    Converged at iteration 11
    




    KMeans(copy_x=True, init='k-means++', max_iter=100, n_clusters=10, n_init=2,
        n_jobs=1, precompute_distances='auto', random_state=None, tol=0.0001,
        verbose=True)



So, we have fitted the algorithm with the dataset. Now, let's check the type of articles that are clustered. 


```python
# Label that is assigned to each articles 
print("Label of each article: {}".format(km.labels_))
```

    Label of each article: [1 7 2 ..., 0 0 1]
    


```python
# Total number of articles in each cluster
import numpy as np

cluster_count = np.unique(km.labels_, return_counts=True)
print("Number of articles in each cluster: {}".format(cluster_count))
```

    Number of articles in each cluster: (array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]), array([730, 377, 326, 148,  36, 295, 168, 168, 244, 181], dtype=int64))
    

Now, let's segregate the articles into their respective clusters.


```python
# Segregating the documents according to the clusters

article_clusters = {}
for i, cluster in enumerate(km.labels_):
    document = articles[i]
    if cluster not in article_clusters.keys():
        article_clusters[cluster] = document
    else:
        article_clusters[cluster] += document
```

#### 4. Tokenizing the collected data

The step in the process is to tokenize the collected data. What do you mean by tokenizing the data?

Tokenization is the process of breaking down the complex sentences to individual words.

> "I like dogs"

So, the above statement can be tokenized to get ("I", "like", "dogs"), this is similar to using **split()** method to tokenize a sentence.

In terms of NLP, tokens better known as **n-grams**, where one word is called **unigram**, 2 words are called as **bigram** and multiple words are called a **n-grams**.


```python
# import statements

from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize, sent_tokenize
from nltk.probability import FreqDist
from collections import defaultdict
from string import punctuation
from heapq import nlargest
import nltk
```


```python
# Let's declare a list of some not so important words that might appear in the articles

special_words = ["billion", "million", "billions", "millions", "$",  "'s", "'d", "\n", "\t", "''", "``", "`", "*"]
stop_words = list(set(stopwords.words("english"))) + list(punctuation) + special_words

print("Stop words are: {}".format(stop_words))
```

    Stop words are: [u'all', u'just', u'being', u'over', u'both', u'through', u'yourselves', u'its', u'before', u'o', u'hadn', u'herself', u'll', u'had', u'should', u'to', u'only', u'won', u'under', u'ours', u'has', u'do', u'them', u'his', u'very', u'they', u'not', u'during', u'now', u'him', u'nor', u'd', u'did', u'didn', u'this', u'she', u'each', u'further', u'where', u'few', u'because', u'doing', u'some', u'hasn', u'are', u'our', u'ourselves', u'out', u'what', u'for', u'while', u're', u'does', u'above', u'between', u'mustn', u't', u'be', u'we', u'who', u'were', u'here', u'shouldn', u'hers', u'by', u'on', u'about', u'couldn', u'of', u'against', u's', u'isn', u'or', u'own', u'into', u'yourself', u'down', u'mightn', u'wasn', u'your', u'from', u'her', u'their', u'aren', u'there', u'been', u'whom', u'too', u'wouldn', u'themselves', u'weren', u'was', u'until', u'more', u'himself', u'that', u'but', u'don', u'with', u'than', u'those', u'he', u'me', u'myself', u'ma', u'these', u'up', u'will', u'below', u'ain', u'can', u'theirs', u'my', u'and', u've', u'then', u'is', u'am', u'it', u'doesn', u'an', u'as', u'itself', u'at', u'have', u'in', u'any', u'if', u'again', u'no', u'when', u'same', u'how', u'other', u'which', u'you', u'shan', u'needn', u'haven', u'after', u'most', u'such', u'why', u'a', u'off', u'i', u'm', u'yours', u'so', u'y', u'the', u'having', u'once', '!', '"', '#', '$', '%', '&', "'", '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~', 'billion', 'million', 'billions', 'millions', '$', "'s", "'d", '\n', '\t', "''", '``', '`', '*']
    

In the next step, we will see the top words from each cluster, this should give us an idea of theme of each cluster.


```python
keywords = {}
counts = {}

for cluster in range(km.n_clusters):
    word_set = word_tokenize(article_clusters[cluster].lower())
    word_set = [word for word in word_set if word not in stop_words and word != ""]
    freq_distribution = FreqDist(word_set)
    keywords[cluster] = nlargest(100, freq_distribution, key=freq_distribution.get)
    counts[cluster] = freq_distribution

# printing the top 100 words from each cluster
for key, value in keywords.iteritems():
    print(key, value[:20])
```

    (0, ['google', 'company', 'said', 'new', 'app', 'like', 'mobile', 'users', 'also', 'one', 'people', 'service', 'companies', 'online', 'year', 'would', 'search', 'technology', 'percent', 'last'])
    (1, ['company', 'said', 'investors', 'year', 'companies', 'new', 'last', 'india', 'round', 'funding', 'capital', 'raised', 'also', 'venture', 'like', 'one', 'valuation', 'online', 'firm', 'investment'])
    (2, ['percent', 'company', 'alibaba', 'said', 'year', 'shares', 'market', 'china', 'sales', 'stock', 'new', 'growth', 'last', 'revenue', 'online', 'chinese', 'investors', 'companies', 'according', 'e-commerce'])
    (3, ['uber', 'company', 'said', 'lyft', 'drivers', 'service', 'china', 'didi', 'new', 'ride-hailing', 'people', 'also', 'ubers', 'investors', 'companies', 'according', 'would', 'rides', 'app', 'year'])
    (4, ['version', 'mp3', 'snippethereis', 'anaudio', 'snippet', 'thissnippet', 'thissnippet.hereis', 'audio', 'snippethere', 'archivedsnippetsarehere.hereis', 'thissnippethereis', 'snippet.hereis', 'soundcloudhereis', 'experimental.hereis', 'herehereis', 'mp3hereis', 'soundcloud.hereis', 'experimentalhereis', 'soundcloudanmp3version', 'experimental'])
    (5, ['facebook', 'twitter', 'users', 'ads', 'company', 'new', 'said', 'video', 'people', 'ad', 'social', 'like', 'app', 'also', 'percent', 'mobile', 'snapchat', 'instagram', 'advertisers', 'data'])
    (6, ['apple', 'said', 'iphone', 'company', 'percent', 'pay', 'sales', 'new', 'watch', 'china', 'year', 'apples', 'also', 'market', 'app', 'mobile', 'according', 'first', 'would', 'quarter'])
    (7, ['amazon', 'said', 'company', 'new', 'service', 'prime', 'online', 'percent', 'delivery', 'services', 'customers', 'amazons', 'also', 'year', 'business', 'products', 'items', 'sales', 'last', 'like'])
    (8, ['said', 'company', 'data', 'companies', 'microsoft', 'software', 'business', 'new', 'cloud', 'percent', 'year', 'technology', 'also', 'would', 'tesla', 'cars', 'like', 'google', 'car', 'last'])
    (9, ['percent', 'revenue', 'company', 'quarter', 'year', 'said', 'share', 'shares', 'rose', 'cents', 'profit', 'business', 'analysts', 'sales', 'net', 'per', 'earnings', 'growth', 'reported', 'forecast'])
    

Here, let's find the unique words in each cluster 


```python
unique_words = {}
for cluster in range(km.n_clusters):
    temp_cluster_1 = list(set(range(km.n_clusters)) - set([cluster]))
    temp_cluster_2 = set(keywords[temp_cluster_1[0]]).union(set(keywords[temp_cluster_1[1]]))
    unique_word = set(keywords[cluster]) - temp_cluster_2
    unique_words[cluster] = nlargest(10, unique_word, key=counts[cluster].get)
```


```python
# printing unique words to a cluster
for i, words in enumerate(unique_words):
    print(i, unique_words[words])
```

    (0, ['app', 'search', 'apps', 'use', 'video', 'product', 'facebook', 'way', 'products', 'content'])
    (1, ['india', 'round', 'funding', 'capital', 'raised', 'venture', 'valuation', 'private', 'startup', 'rs'])
    (2, ['alibaba', 'chinese', 'quarter', 'inc.', 'u.s.', 'share', 'biggest', 'stake', 'earnings', 'offering'])
    (3, ['uber', 'lyft', 'drivers', 'didi', 'ride-hailing', 'ubers', 'rides', 'cities', 'kuaidi', 'driver'])
    (4, ['version', 'mp3', 'snippethereis', 'anaudio', 'snippet', 'thissnippet', 'thissnippet.hereis', 'audio', 'archivedsnippetsarehere.hereis', 'snippethere'])
    (5, ['twitter', 'snapchat', 'instagram', 'advertisers', 'news', 'advertising', 'brands', 'user', 'facebooks', 'feature'])
    (6, ['apple', 'iphone', 'watch', 'apples', 'quarter', 'iphones', 'smartphone', 'samsung', 'u.s.', 'payments'])
    (7, ['prime', 'amazons', 'items', 'amazon.com', 'shipping', 'sellers', 'retailer', 'shoppers', 'customer', 'jet'])
    (8, ['microsoft', 'cloud', 'tesla', 'cars', 'car', 'model', 'computing', 'vehicles', 'executive', 'systems'])
    (9, ['quarter', 'share', 'rose', 'cents', 'profit', 'analysts', 'net', 'earnings', 'reported', 'forecast'])
    

By now, we know what's the theme of each cluster

* Cluster 0 - Apps
* Cluster 1 - Funding
* Cluster 2 - Company Earnings
* Cluster 3 - Car Transportation
* Cluster 4 - Music (Looks like an outlier)
* Cluster 5 - Social Media
* Cluster 6 - Phone
* Cluster 7 - Amazon
* Cluster 8 - Innovation
* Cluster 9 - Stocks

Disclaimer - The clusters might not be accurately created, this is done just to give an overview on how the articles will be clustered.


```python
categories = {0: "Apps", 1: "Funding", 2: "Company Earnings", 3: "Car Transportation", 4: "Music", 5: "Social Media", 6: "Phone", 7: "Amazon", 8: "Innovation", 9: "Stocks"}
```

#### 5. Predicting the label for an article


```python
# We are using KNeighborsClassifier for predicting the class for an article

from sklearn.neighbors import KNeighborsClassifier
clf = KNeighborsClassifier()
```


```python
# Fitting the data to KNeighborsClassifier

clf.fit(articles_tfidf, km.labels_)
```




    KNeighborsClassifier(algorithm='auto', leaf_size=30, metric='minkowski',
               metric_params=None, n_jobs=1, n_neighbors=5, p=2,
               weights='uniform')




```python
predict_airbnb = " Online room renting service Airbnb Inc said on Thursday it had raised $1 billion in its latest round of funding, valuing the company at $31 billion.The company turned in a profit on an EBITDA basis in the second half of 2016 and expects to continue to be profitable this year, the source said, adding that Airbnb had no plans to go public anytime soon. The company is locked in an intensifying global battle with regulators who say the service takes affordable housing off the market and drives up rental prices.Airbnb raised $447.85 million as part of the funding, a source close to the company told Reuters. The company said in September it had raised about $555 million as part of the same round of funding. Airbnb, which operates in more than 65,000 cities, has enjoyed tremendous growth as it pushes ahead with its plans of global expansion"
```


```python
airbnb_transform = vectorizer.transform([predict_airbnb.decode('utf8').encode('ascii', errors='ignore')])
```


```python
label = clf.predict(airbnb_transform)[0]

if label in categories:
    print("Category belongs to the category: {}".format(categories[label]))
else:
    print("Unknown category")
```

    Category belongs to the category: Apps
    

Hope you understood the basics of a Natural Language Processing problem.

This basic introduction is based on [Swetha Kolalapudi](https://www.pluralsight.com/courses/python-natural-language-processing)'s session.


```python

```

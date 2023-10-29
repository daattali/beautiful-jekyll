
const cacheName = 'sound-pwa-v1';
const filesToCache = [
  '/blog/bowl',
  '/blog/bowl/index.html',
  '/blog/bowl/1_root.mp3',
  '/blog/bowl/2_sacral.mp3',
  '/blog/bowl/3_solar_plexus.mp3',
  '/blog/bowl/4_heart.mp3',
  '/blog/bowl/6_eye.mp3',
  '/blog/bowl/5_throat.mp3',
  '/blog/bowl/7_crown.mp3',
];

self.addEventListener('install', event => {
  console.log('Installing service worker');
  event.waitUntil(
    caches.open(cacheName)
      .then(cache => {
        console.log('Caching files');
        return cache.addAll(filesToCache);
      })
  );
});

self.addEventListener('activate', event => {
  console.log('Activating service worker');
  event.waitUntil(
    caches.keys().then(keyList => {
      return Promise.all(keyList.map(key => {
        if (key !== cacheName) {
          console.log('Deleting old cache');
          return caches.delete(key);
        }
      }));
    })
  );
});

self.addEventListener('fetch', event => {
  console.log('Fetching:', event.request.url);
  event.respondWith(
    caches.match(event.request).then(response => {
      return response || fetch(event.request);
    })
  );
});
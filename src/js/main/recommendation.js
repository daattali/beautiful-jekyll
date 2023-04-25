(function () {
    'use strict';

    var recommendation = document.querySelector('.recommendation');
    var isVisible = false;

    if (recommendation) {
        // Back to top button
        var goBackToTop = recommendation.querySelector('.message button');
        goBackToTop.addEventListener('click', function () {
            scrollToTop();
            return false;
        });

        // Hide
        document.addEventListener('stillReading', function (elem) {
            if (isVisible) {
                recommendation.style.bottom = '-100%';
                isVisible = false;
            }
        }, false);

        // Show
        document.addEventListener('finishedReading', function (elem) {
            if (!isVisible) {
                recommendation.style.bottom = '0%';
                isVisible = true;
            }
        }, false);
    }

    var timeOut;
    function scrollToTop() {
        if (document.body.scrollTop != 0 || document.documentElement.scrollTop != 0) {
            window.scrollBy(0, -50);
            timeOut = setTimeout(scrollToTop, 10);
        }
        else clearTimeout(timeOut);
    }
})();

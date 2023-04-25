(function () {
    'use strict';

    var post = document.querySelector('.post-content');
    var timeBar = document.querySelector('.time-bar');
    var shouldShow = true;

    if (post && timeBar) {
        var lastScrollTop = 0;
        var maxScrollTop = post.scrollHeight;

        var completed = timeBar.querySelector('.completed');
        var remaining = timeBar.querySelector('.remaining');
        var timeCompleted = timeBar.querySelector('.time-completed');
        var timeRemaining = timeBar.querySelector('.time-remaining');

        document.addEventListener('scroll', function () {
            var scrollTop = window.pageYOffset || document.documentElement.scrollTop;

            if (scrollTop > lastScrollTop && shouldShow) {
                timeBar.style.bottom = '0%';
            } else {
                timeBar.style.bottom = '-100%';
            }

            if (scrollTop <= maxScrollTop) {
                var percentage = scrollTop / maxScrollTop;

                var completedVal = (percentage * 100).toFixed(2);
                var remainingVal = 100 - parseFloat(completedVal);
                completed.style.width = completedVal.toString() + '%';
                remaining.style.width = remainingVal.toString() + '%';

                var totalSeconds = parseInt(timeBar.getAttribute('data-minutes')) * 60;

                var completedTime = parseInt(percentage * totalSeconds);
                var completedMin = parseInt(completedTime / 60);
                var completedSec = parseInt((completedTime / 60 - completedMin) * 60);

                var remainingTime = totalSeconds - completedTime;
                var remainingMin = parseInt(remainingTime / 60);
                var remainingSec = parseInt((remainingTime / 60 - remainingMin) * 60);

                completedMin = (completedMin < 10) ? '0' + completedMin : completedMin;
                completedSec = (completedSec < 10) ? '0' + completedSec : completedSec;
                remainingMin = (remainingMin < 10) ? '0' + remainingMin : remainingMin;
                remainingSec = (remainingSec < 10) ? '0' + remainingSec : remainingSec;

                timeCompleted.innerText = completedMin + ':' + completedSec;
                timeRemaining.innerText = remainingMin + ':' + remainingSec;

                shouldShow = true;

                triggerStillReading();
            } else {
                completed.style.width = '100%';
                remaining.style.width = '0%';

                var minutes = parseInt(timeBar.getAttribute('data-minutes'));
                minutes = (minutes < 10) ? '0' + minutes : minutes;

                timeCompleted.innerText = '00:00';
                timeRemaining.innerText = minutes + ':00';

                shouldShow = false;

                triggerFinishedReading();
            }

            lastScrollTop = scrollTop;
        });
    }

    function triggerStillReading() {
        var readEvent = document.createEvent('CustomEvent');
        readEvent.initCustomEvent('stillReading');
        document.dispatchEvent(readEvent);
    }

    function triggerFinishedReading() {
        var readEvent = document.createEvent('CustomEvent');
        readEvent.initCustomEvent('finishedReading');
        document.dispatchEvent(readEvent);
    }
})();

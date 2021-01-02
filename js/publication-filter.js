$(document).ready(function () {

    // get recent five years
    const present = new Date().getFullYear();
    const older = present - 5;
    const recent_years = [present, present - 1, present - 2, present - 3, present - 4];

    // add recent five years filter button dynamically
    $('#filterByYear').append('<button type="button" class="btn  filterBtn selected" id="all">All</button>');
    for (let year = present; year > older; year--) {
        $('#filterByYear').append('<button type="button" class="btn  filterBtn " id="' + year + '">' + year + '</button>');
    }
    $('#filterByYear').append('<button type="button" class="btn filterBtn " id="older">Older</button>');

    // click on button  in the filter area
    $("button").click(function (event) {
        let filter_id = event.target.id;
        // remove the already selected filter
        $('.selected').removeClass("selected");
        // highlighted the selected filter
        $('#' + filter_id).addClass("selected");
        let filter_class = '.' + filter_id;
        if (filter_id == 'all') {
            $('.papers').show();
        } else if (filter_id == 'older') {
            $('.papers').hide();
            // show all publications except the recent years
            $('.papers').not('.' + recent_years[0]).not('.' + recent_years[1])
                .not('.' + recent_years[2]).not('.' + recent_years[3]).not('.' + recent_years[4]).show();
        } else {
            // show only the selected filtered papers
            $(filter_class).show();
            $('.papers').not(filter_class).hide();
        }
    });
})
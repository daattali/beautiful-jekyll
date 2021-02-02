$(document).ready(function () {

    // get recent five years
    const present = new Date().getFullYear();
    const older = present - 10;
    const recent_years = [present, present - 1, present - 2, present - 3, present - 4, present-5, present-6, present-7,present-8, present-9];

    // add recent five years filter button dynamically
    $('#filterEventByYear').append('<button type="button" class="btn  filterBtn selected" id="all">All</button>');
    for (let year = present; year > older; year--) {
        $('#filterEventByYear').append('<button type="button" class="btn  filterBtn " id="' + year + '">' + year + '</button>');
    }
    $('#filterEventByYear').append('<button type="button" class="btn filterBtn " id="older">Older</button>');

    // click on button  in the filter area
    $("button").click(function (event) {
        let filter_id = event.target.id;
        // remove the already selected filter
        $('.selected').removeClass("selected");
        // highlighted the selected filter
        $('#' + filter_id).addClass("selected");
        let filter_class = '.' + filter_id;
        if (filter_id == 'all') {
            $('.events').show();
        } else if (filter_id == 'older') {
            $('.events').hide();
            // show all publications except the recent years
            $('.events').not('.' + recent_years[0]).not('.' + recent_years[1])
                .not('.' + recent_years[2]).not('.' + recent_years[3]).not('.' + recent_years[4]).not('.' + recent_years[5])
				.not('.' + recent_years[6]).not('.' + recent_years[7]).not('.' + recent_years[8]).not('.' + recent_years[9]).show();
        } else {
            // show only the selected filtered papers
            $(filter_class).show();
            $('.events').not(filter_class).hide();
        }
    });
})
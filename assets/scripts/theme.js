const LS_THEME_KEY = 'theme';

// get theme in local storage
function getTheme() {
	const theme = localStorage.getItem(LS_THEME_KEY);
	const themeIcon = $('#themeIcon');
	const themeWrap = $('#theme');

	if (theme && theme === 'dark') {
		$(':root').attr('data-theme', 'dark');
		themeIcon.removeClass('fa-sun').addClass('fa-moon');
		themeWrap.css('flex-direction', 'row-reverse');
	} else {
		$(':root').attr('data-theme', 'light');
		themeIcon.removeClass('fa-moon').addClass('fa-sun');
		themeWrap.css('flex-direction', 'row');
	}
}

$(document).ready(function () {
	// get theme
	getTheme();

	// change theme
	$('#themeBtn').click(function () {
		const root = $(':root');
		const themeIcon = $('#themeIcon');
		const themeWrap = $('#theme');

		if (themeIcon.hasClass('fa-sun')) {
			themeIcon.removeClass('fa-sun').addClass('fa-moon');
			themeWrap.css('flex-direction', 'row-reverse');
			root.attr('data-theme', 'dark');
			localStorage.setItem(LS_THEME_KEY, 'dark');
		} else {
			themeIcon.removeClass('fa-moon').addClass('fa-sun');
			themeWrap.css('flex-direction', 'row');
			root.attr('data-theme', 'light');
			localStorage.setItem(LS_THEME_KEY, 'light');
		}
	});
});

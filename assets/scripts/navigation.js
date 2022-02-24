const NAV_LINKS = {
	HOME: 'home',
	ABOUT: 'about',
	PORTFOLIO: 'portfolio',
	CONTACT: 'contact',
};

const NAV_LIST = [
	{
		link: NAV_LINKS.HOME,
		iconClass: 'fas fa-home',
		label: 'Home',
	},
	{
		link: NAV_LINKS.ABOUT,
		iconClass: 'fas fa-user-alt',
		label: 'About Me',
	},
	{
		link: NAV_LINKS.PORTFOLIO,
		iconClass: 'fas fa-briefcase',
		label: 'Portfolio',
	},
	{
		link: NAV_LINKS.CONTACT,
		iconClass: 'fas fa-envelope',
		label: 'Contact',
	},
];

const LINK_KEY = 'data-link';

let currentLink = NAV_LINKS.HOME;

// get initial component
function getComponent(link = NAV_LINKS.HOME) {
	if (!link || link === '') return;
	// remove current
	$(`.nav-link[data-link=${currentLink}]`).removeClass('active');
	$(`.nav-link[data-link=${link}]`).addClass('active');

	// add new component
	$(`#${currentLink}`).fadeOut(750).css('display', 'none');
	$(`#${link}`).fadeIn(750);
	currentLink = link;
}

// render navigation
function renderNavigation() {
	let mobileXml = '',
		desktopXml = '';

	NAV_LIST.forEach((item) => {
		mobileXml += `<li class="nav-link" ${LINK_KEY}="${item.link}"><i class="${item.iconClass}"></i></li>`;

		desktopXml += `<li class="nav-link" ${LINK_KEY}="${item.link}">${item.label}</li>`;
	});

	mobileXml += `<li class="nav-link" ${LINK_KEY}=""><a href="https://www.topcv.vn/xem-cv/VVJaVFMFB1UBAgwCBFFRAldXCQJQU1ZSAVNUBg5be6" target="_blank"><i class="fas fa-file-pdf"></i></a></li>`;
	desktopXml += `<li class="nav-link" ${LINK_KEY}=""><a href="https://www.topcv.vn/xem-cv/VVJaVFMFB1UBAgwCBFFRAldXCQJQU1ZSAVNUBg5be6" target="_blank">My CV</a></li>`;

	$('#mobileNavLinks').html(mobileXml);
	$('#desktopNavLinks').html(desktopXml);
}

$(document).ready(function () {
	// render mobile navigation
	renderNavigation();

	// get home
	getComponent(currentLink);

	// link & render component
	$('.nav-link').click(function () {
		const link = $(this).attr(LINK_KEY);
		getComponent(link);
	});
});

const DATA_KEY = 'data-key';
const DETAIL_KEY = 'data-id';

const OPTIONS = [
	{
		key: 'all',
		label: 'All',
		title: 'All Projects',
	},
	{
		key: 'mern',
		label: 'MERN Stack',
		title: 'MERN Stack Projects',
	},
	{
		key: 'learning',
		label: 'Learning',
		title: 'Projects For Learning',
	},
	{
		key: 'sharing',
		label: 'Sharing',
		title: 'Projects For Sharing',
	},
	{
		key: 'embedd',
		label: 'embedded',
		title: 'Embedded Projects',
	},
	{
		key: 'others',
		label: 'Others',
		title: 'Other Projects',
	},
];

const PROJECTS = [
	{
		id: '0',
		key: 'embedd',
		img: './assets/projects/iot-module.jpg',
		projectName: 'IoT Module for BCS2',
		projectTech: 'C/C++,Industrial Communication, web server, HTML, CSS, Javascript, MODBUS',
		video: '#',
		github: 'https://github.com/nhim411/IoT-module-for-BCS2',
		liveDemo: '#',
	},
];

const PROJECTS_DETAILS = [
	{
		id: '0',
		title: 'TodoApp - A Simple todo App built with React',
		contentList: [
			{
				label: 'Description',
				content: `My final year project.`,
			},
			{
				label: 'Created',
				content: '1-8-2020',
			},
			{
				label: 'Completed',
				content: '28-12-2020',
			},
			{
				label: 'Features',
				content: 'Connect with BCS2 via Modbus, web server',
			},
			{
				label: 'Status',
				content: 'Done',
			},
			{
				label: 'Technologies',
				content: 'C/C++, Industrial communication, web server, HTML, CSS, JS',
			},
			{
				label: 'Hosting, Storage',
				content: 'host in SPIFFS of ESP32',
			},
			{
				label: 'Source Code',
				content: 'https://github.com/nhim411/IoT-module-for-BCS2',
				isLink: true,
			},
			// {
			// 	label: 'Video Demo',
			// 	content: 'https://github.com/nhim411/IoT-module-for-BCS2',
			// 	isLink: false,
			// },
		],
	},
];

let currentOptionKey = OPTIONS[0].key;

function renderOptions() {
	let xml = '';

	OPTIONS.forEach((item) => {
		xml += `<li ${DATA_KEY}="${item.key}" class="portfolio-menu-option ${item.key === currentOptionKey ? 'active' : ''}">${item.label}</li>`;
	});

	$('#portfolioMenu').html(xml);
}

function renderProject(projects = []) {
	let xml = '';
	projects.forEach((project) => {
		const { id, key, img, projectName, projectTech, video, github, liveDemo } = project;

		xml += `<li class="portfolio-item">
	<img src="${img}" alt="Portfolio Photo" />
	<div class="portfolio-item-detail">
		<h2 class="project-name">${projectName}</h2>
		<p class="project-tech">${projectTech}</p>
		<div class="d-flex">
			<a class="cur-pointer show-detail" ${DETAIL_KEY}="${id}">
				<i class="fas fa-info-circle project-icon"></i>
			</a>
			${
				video && video !== ''
					? `<a href="${video}" target="_blank">
							<i	i class="fas fa-play-circle project-icon"></i>
						</a>`
					: ''
			}
			${
				github && github !== ''
					? `	<a href="${github}" target="_blank">
								<i class="fab fa-github project-icon"></i>
						</a>`
					: ''
			}
		${
			liveDemo && liveDemo !== ''
				? `<a href="${liveDemo}" target="_blank">
					<i class="fas fa-eye project-icon"></i>
				</a>`
				: ''
		}

		</div>
	</div>
</li>`;
	});

	$('#portfolioList').fadeOut().html(xml).fadeIn(350);
	$('.show-detail').click(function () {
		const id = $(this).attr(DETAIL_KEY);
		showProjectDetailDialog(id);
	});
}

function showProjectDetailDialog(id = '') {
	if (!id || id === '') return;

	const project = PROJECTS_DETAILS.find((i) => i.id === id);
	if (!project) return;

	const { contentList, title } = project;

	let xml = '';
	contentList.forEach((item) => {
		xml += `<li class="dialog-content-item">
	<span class="label">${item.label}:&nbsp;</span>
	<span class="content">
		${item.isLink ? `<a class="link" href="${item.content}" target="_blank">${item.content}</a>` : item.content}
	</span>
</li>`;
	});

	$('#projectDiaglogTitle').text(title);
	$('#projectDialogContent').html(xml);
	$('#overlay').show(250);
	$('#projectDialog').show(250);

	$('#closeDialogBtn').click(() => {
		$('#overlay').hide(350);
		$('#projectDialog').hide(500);
	});
}

$(document).ready(function () {
	renderOptions();

	// render init all projects
	renderProject(PROJECTS);

	// filter project
	$('.portfolio-menu-option').click(function () {
		if ($(this).hasClass('active')) {
			return;
		}

		// change active menu item
		currentOptionKey = $(this).attr('data-key');
		$('.portfolio-menu-option.active').removeClass('active');
		$(this).addClass('active');

		// change menu title
		const newLabel = OPTIONS.find((i) => i.key === currentOptionKey).title;
		$('#portfolioMenuLabel').text(newLabel);

		// filter
		if (currentOptionKey === 'all') {
			renderProject(PROJECTS);
		} else {
			const filtered = PROJECTS.filter((i) => i.key === currentOptionKey);
			renderProject(filtered);
		}
	});
});

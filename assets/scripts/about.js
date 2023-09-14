const INTRODUCES = [
	'🤵 I graduated at DUT - Danang University of Technology. My major is Control Engineering and Automation',
	'👨‍💻  I\'m a Front-end Developer',
	'🎯 Future Goals: Learn more technologies. Learning to become a full-stack developer',
];

const SKILLS = [
	{
		label: 'Front-end Technologies',
		content: 'HTML5, CSS3, SCSS, ReactJS, Vue, Javascript, Typescript',
	},
	{
		label: 'Embedded Technologies',
		content: 'C/C++ Programming, PLC Programming',
	},
	// {
	// 	label: 'Back-end Technologies',
	// 	content: 'NodeJS (ExpressJS), RESTful API, Pug Engine, MongoDB',
	// },
	{
		label: 'Development Tools / Teamwork Tools',
		content: 'Vscode, Git, Backlog',
	},
	{
		label: 'Others',
		content: 'Docker, Linux system',
	},
];

function renderIntroduces() {
	let xml = '<p class="label">Overview</p>';
	INTRODUCES.forEach((item) => {
		xml += `<li class="about-intro-item">${item}</li>`;
	});
	$('#aboutIntro').html(xml);
}

function renderSkills() {
	let xml = '';
	SKILLS.forEach((skill) => {
		xml += `<li class="about-skill-item"><p class="label">${skill.label}</p><p class="content">${skill.content}</p></li>`;
	});
	$('#aboutSkill').html(xml);
}

$(document).ready(function () {
	// render introduces
	renderIntroduces();

	// render skills
	renderSkills();
});

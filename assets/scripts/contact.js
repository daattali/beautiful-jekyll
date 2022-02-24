const CONTACT_INFOS = [
	{
		label: 'Full Name',
		content: 'Le Hoai Nam',
	},
	{
		label: 'Birthday',
		content: '04-11-1998',
	},
	{
		label: 'Address',
		content: 'Da Nang city, Viet Nam',
	},
	{
		label: 'Graduate',
		content: 'Danang University of Technology HCM City (DUT)',
	},
	{
		label: 'Major',
		content: 'Control Engineering and Automation',
	},
	{
		label: 'Status',
		content: 'Open to offers',
	},
];

const CONTACT_SOCIAL_NETWORKS = [
	{
		label: 'Phone',
		content: '(+84) xxxxxxxxx',
		link: '#',
		iconClass: 'fas fa-phone-square-alt',
	},
	{
		label: 'Email',
		content: 'lehoainam1998@gmail.com',
		link: 'https://mail.google.com/mail/u/0/?view=cm&fs=1&tf=1&to=lehoainam1998@gmail.com',
		iconClass: 'fas fa-envelope',
	},
	{
		label: 'Linkedin',
		content: 'nhim411',
		link: 'https://www.linkedin.com/in/nhim411/',
		iconClass: 'fab fa-linkedin',
	},
	{
		label: 'Github',
		content: 'nhim411',
		link: 'https://github.com/nhim411',
		iconClass: 'fab fa-github',
	},
	{
		label: 'Facebook',
		content: 'lhnam411',
		link: 'https://www.facebook.com/lhnam411/',
		iconClass: 'fab fa-facebook',
	},
	{
		label: 'Instagram',
		content: 'namlhh',
		link: 'https://www.instagram.com/namlhh/',
		iconClass: 'fab fa-instagram-square',
	},
];

function renderContactInfos() {
	let xml = '';
	CONTACT_INFOS.forEach((item) => {
		xml += `<li class="contact-info-item">
    <span class="label">${item.label}:&nbsp;&nbsp;</span>
    <span class="content">${item.content}</span>
  </li>`;
	});
	$('#contactInfo').html(xml);
}

function renderSocialNetworks() {
	let xml = '';
	CONTACT_SOCIAL_NETWORKS.forEach((item) => {
		xml += `<li>
      <i class="${item.iconClass} contact-icon"></i>
      <span class="label">${item.label}:&nbsp;&nbsp;</span>
      <a href="${item.link}" class="link content">${item.content}</a>
    </li>`;
	});

	xml += `<li>
	<i class="fas fa-download contact-icon"></i>
	<span class="label">Download My CV:&nbsp;&nbsp;</span>
	<a href="https://www.topcv.vn/xem-cv/VVJaVFMFB1UBAgwCBFFRAldXCQJQU1ZSAVNUBg5be6" class="link content">Link</a>
</li>`;

	$('#contactSocialNetwork').html(xml);
}

$(document).ready(function () {
	renderContactInfos();
	renderSocialNetworks();
});

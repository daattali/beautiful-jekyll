const options = {
  bottom: '64px', // default: '32px'
  right: '32px', // default: '32px'
  left: '32px', // default: 'unset'
  time: '0.5s', // default: '0.3s'
  mixColor: '#D1DBBF', // default: '#fff'
  backgroundColor: '#D1DBBF',  // default: '#fff'
  buttonColorDark: '#100f2c',  // default: '#100f2c'
  buttonColorLight: '#D1DBBF', // default: '#fff'
  saveInCookies: true, // default: true,
  label: '🌓', // default: ''
  autoMatchOsTheme: false // default: true
}

const darkmode = new Darkmode(options);
darkmode.showWidget();

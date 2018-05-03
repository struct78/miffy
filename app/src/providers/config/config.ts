export let Config = {
  sandbox: true,
  dns_provider: {
    sandbox: 'getsandbox.com',
    production: 'dynu.net'
  },
  loading: {
    title: 'Finding Nightlight',
    spinner: 'crescent',
    duration: 3000
  },
  alert: {
    title: 'Connection failed',
    message: 'Do you want to try again?',
  }
};

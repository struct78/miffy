export let Config = {
  sandbox: false,
  dns_provider: {
    sandbox: 'getsandbox.com',
    production: 'dynu.net/api'
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

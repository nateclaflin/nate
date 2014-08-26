App = Ember.Application.create();

App.Router.map(function() {
  // put your routes here
  this.route('index', {path: "/"});
  this.route('experience', {path: "/experience"});
  this.route('examples', {path: "/examples"});
  this.route('html', { path: '/html'});
  this.route('java', { path: '/java'});
  this.route('cprog', {path: '/cprog'});
  this.route('assembly', {path: '/assembly'});
});

App.IndexRoute = Ember.Route.extend({
  model: function() {
    return ['red', 'yellow', 'blue'];
  }
});

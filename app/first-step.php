<?php

require_once('RatpClient.php'); 
require_once('JorneyFinder.php');

$c = new RatpClient();
$r = $c->getMetro('gare');
$routes = $c->getRoutes();
// $matrix = $c->getMatrix($routes);

$jf = new JourneyFinder();

$journey = $jf->getJourney($routes, 'Nation (Paris)', 'Opéra (Paris)');

echo "<pre>";
print_r($journey);
echo "</pre>";
// https://api.navitia.io/v1/coverage/sandbox/networks/network%3ARAT%3A1/routes?depth=3&
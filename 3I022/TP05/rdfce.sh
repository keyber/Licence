#!/bin/sh

rdf $1 o1rdfce.inr o2rdfce.inr
chmod 755 o1rdfce.inr
chmod 755 o2rdfce.inr
ce o1rdfce.inr o1rdfce.inr
ce o2rdfce.inr o2rdfce.inr


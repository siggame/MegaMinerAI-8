#!/usr/bin/env python

from aws_creds import access_cred, secret_cred
import boto
import time

import beanstalkc
import json

stalk = beanstalkc.Connection()

stalk.watch('free-gladiators')
stalk.use('free-gladiators')

print "clearing the gladiator pool..."
while stalk.stats_tube('free-gladiators')['current-jobs-ready'] > 0:
    j = stalk.reserve()
    j.delete()

count = 16
print "spinning up %i gladiators..." % count
conn = boto.connect_ec2(access_cred, secret_cred)
gladiator_image = conn.get_image('ami-ef63ac86')
reservation = gladiator_image.run(min_count = count, max_count = count,
                                  instance_type='c1.medium', 
                                  key_name = 'MND_EC2_keypair',
                                  security_groups = ['MND_SecurityGroup'])

while True:
    try:
        states = [x.update() for x in reservation.instances]
        if all([x == u'running' for x in states]):
            break
        print states
    except boto.exception.EC2ResponseError:
        pass
    time.sleep(5)
    
gladiator_pairs = list()
for instance in reservation.instances:
    pair_thing = [instance.public_dns_name, instance.public_dns_name]
    gladiator_pairs.append(pair_thing)
    
#gladiator_pairs = [ ['localhost', 'localhost'],
#                    ['localhost', 'localhost'] ]

#print gladiator_pairs

print "loading gladiators into the pool..."
for pair in gladiator_pairs:
    s = json.dumps(pair)
    stalk.put(s)

stalk.close()
print "done! light the blaster!"

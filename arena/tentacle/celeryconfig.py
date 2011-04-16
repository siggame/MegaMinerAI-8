BROKER_HOST = 'localhost'
BROKER_PORT = 5672
BROKER_USER = 'mastercontroller'
BROKER_PASSWORD = 'XSPnDy5G'
BROKER_VHOST = 'monster'

CELERY_RESULT_BACKEND = 'amqp'

CELERY_IMPORTS = ("tentacle", )

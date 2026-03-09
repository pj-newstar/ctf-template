FROM php:7.4-apache

ENV FLAG=flag{test_flag}

COPY ./src/ /var/www/html/

CMD [ "apache2-foreground" ]

EXPOSE 80
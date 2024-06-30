# Eclipse Kapua with OpenSearch

This section provides a complete understanding of what I did to change the default datastore of Kapua from ElasticSearch to OpenSearch and the current limitations of Kapua around security.

The key is the `docker-compose.yml` provided in this section:

```yaml
es:
  container_name: es
  image: opensearchproject/opensearch:1.0.0
  ports:
    - "9200:9200"
    - "9300:9300"
    - "9600:9600"
  environment:
    - cluster.name=kapua-datastore
    - discovery.type=single-node
    - plugins.security.disabled=true
    - transport.host=_site_
    - transport.ping_schedule=-1
    - transport.tcp.connect_timeout=30s
es-dashboard:
  container_name: es-dashboard
  image: opensearchproject/opensearch-dashboards:1.0.0
  ports:
    - "5601:5601"
  environment:
    - OPENSEARCH_HOSTS=https://es:9200
    - plugins.security.disabled=true
```

With these changes, we select the version of OpenSearch and also include the es-dashboard container to install OpenSearch Dashboard. For both functionalities, we have disabled security and security plugins because the Kapua documentation and Kapua GitHub have explicitly informed that Kapua does not support authentication into Elastic Search.

perl

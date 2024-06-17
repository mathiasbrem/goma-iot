{
  "annotations": {
    "list": [
      {
        "builtIn": 1,
        "datasource": {
          "type": "grafana",
          "uid": "-- Grafana --"
        },
        "enable": true,
        "hide": true,
        "iconColor": "rgba(0, 211, 255, 1)",
        "name": "Annotations & Alerts",
        "type": "dashboard"
      }
    ]
  },
  "editable": true,
  "fiscalYearStartMonth": 0,
  "graphTooltip": 0,
  "id": 2,
  "links": [],
  "panels": [
    {
      "datasource": {
        "type": "grafana-opensearch-datasource",
        "uid": "bdnts6dprmnlsc"
      },
      "gridPos": {
        "h": 4,
        "w": 4,
        "x": 0,
        "y": 0
      },
      "id": 7,
      "options": {
        "code": {
          "language": "plaintext",
          "showLineNumbers": false,
          "showMiniMap": false
        },
        "content": "<img src=\"https://icmc.usp.br/templates/icmc2015/img/logo.png\" alt=\"Logo ICMC\" style=\"display: block; margin: 0 auto;\">\n",
        "mode": "html"
      },
      "pluginVersion": "11.0.0",
      "targets": [
        {
          "alias": "",
          "bucketAggs": [
            {
              "field": "timestamp",
              "id": "2",
              "settings": {
                "interval": "auto"
              },
              "type": "date_histogram"
            }
          ],
          "datasource": {
            "type": "grafana-opensearch-datasource",
            "uid": "bdnts6dprmnlsc"
          },
          "format": "table",
          "metrics": [
            {
              "id": "1",
              "type": "count"
            }
          ],
          "query": "",
          "queryType": "lucene",
          "refId": "A",
          "timeField": "timestamp"
        }
      ],
      "transparent": true,
      "type": "text"
    },
    {
      "datasource": {
        "type": "grafana-opensearch-datasource",
        "uid": "bdnts6dprmnlsc"
      },
      "fieldConfig": {
        "defaults": {
          "color": {
            "mode": "continuous-GrYlRd"
          },
          "mappings": [],
          "thresholds": {
            "mode": "absolute",
            "steps": [
              {
                "color": "green"
              },
              {
                "color": "red",
                "value": 80
              }
            ]
          },
          "unit": "watt"
        },
        "overrides": []
      },
      "gridPos": {
        "h": 4,
        "w": 8,
        "x": 4,
        "y": 0
      },
      "id": 3,
      "options": {
        "displayMode": "lcd",
        "maxVizHeight": 300,
        "minVizHeight": 16,
        "minVizWidth": 8,
        "namePlacement": "auto",
        "orientation": "horizontal",
        "reduceOptions": {
          "calcs": [
            "lastNotNull"
          ],
          "fields": "",
          "values": false
        },
        "showUnfilled": true,
        "sizing": "auto",
        "valueMode": "color"
      },
      "pluginVersion": "11.0.0",
      "targets": [
        {
          "alias": "",
          "bucketAggs": [
            {
              "field": "timestamp",
              "id": "2",
              "settings": {
                "interval": "auto"
              },
              "type": "date_histogram"
            }
          ],
          "datasource": {
            "type": "grafana-opensearch-datasource",
            "uid": "bdnts6dprmnlsc"
          },
          "format": "table",
          "metrics": [
            {
              "field": "metrics.power.dbl",
              "hide": false,
              "id": "1",
              "type": "avg"
            }
          ],
          "query": "",
          "queryType": "lucene",
          "refId": "A",
          "timeField": "timestamp"
        }
      ],
      "title": "Potência Utilizada",
      "transparent": true,
      "type": "bargauge"
    },
    {
      "datasource": {
        "type": "grafana-opensearch-datasource",
        "uid": "bdnts6dprmnlsc"
      },
      "fieldConfig": {
        "defaults": {
          "mappings": [],
          "thresholds": {
            "mode": "percentage",
            "steps": [
              {
                "color": "green"
              },
              {
                "color": "orange",
                "value": 70
              },
              {
                "color": "red",
                "value": 85
              }
            ]
          }
        },
        "overrides": []
      },
      "gridPos": {
        "h": 4,
        "w": 5,
        "x": 16,
        "y": 0
      },
      "id": 2,
      "options": {
        "minVizHeight": 75,
        "minVizWidth": 75,
        "orientation": "auto",
        "reduceOptions": {
          "calcs": [
            "lastNotNull"
          ],
          "fields": "",
          "values": false
        },
        "showThresholdLabels": false,
        "showThresholdMarkers": true,
        "sizing": "auto"
      },
      "pluginVersion": "11.0.0",
      "targets": [
        {
          "alias": "",
          "bucketAggs": [
            {
              "field": "timestamp",
              "id": "2",
              "settings": {
                "interval": "auto"
              },
              "type": "date_histogram"
            }
          ],
          "datasource": {
            "type": "grafana-opensearch-datasource",
            "uid": "bdnts6dprmnlsc"
          },
          "format": "table",
          "metrics": [
            {
              "field": "metrics.temperature.dbl",
              "id": "1",
              "type": "avg"
            }
          ],
          "query": "metrics.sensor_type.str:$sensor_type AND metrics.sensor_id.str:$sensor_id",
          "queryType": "lucene",
          "refId": "A",
          "timeField": "timestamp"
        }
      ],
      "title": "Temperatura",
      "transparent": true,
      "type": "gauge"
    },
    {
      "datasource": {
        "type": "grafana-opensearch-datasource",
        "uid": "bdnts6dprmnlsc"
      },
      "fieldConfig": {
        "defaults": {
          "color": {
            "mode": "continuous-RdYlGr",
            "seriesBy": "max"
          },
          "custom": {
            "axisBorderShow": false,
            "axisCenteredZero": false,
            "axisColorMode": "text",
            "axisLabel": "",
            "axisPlacement": "auto",
            "barAlignment": 0,
            "drawStyle": "bars",
            "fillOpacity": 20,
            "gradientMode": "scheme",
            "hideFrom": {
              "legend": false,
              "tooltip": false,
              "viz": false
            },
            "insertNulls": false,
            "lineInterpolation": "smooth",
            "lineWidth": 3,
            "pointSize": 5,
            "scaleDistribution": {
              "type": "linear"
            },
            "showPoints": "auto",
            "spanNulls": false,
            "stacking": {
              "group": "A",
              "mode": "none"
            },
            "thresholdsStyle": {
              "mode": "off"
            }
          },
          "mappings": [],
          "thresholds": {
            "mode": "absolute",
            "steps": [
              {
                "color": "green"
              },
              {
                "color": "red",
                "value": 80
              }
            ]
          },
          "unit": "percent"
        },
        "overrides": []
      },
      "gridPos": {
        "h": 8,
        "w": 12,
        "x": 0,
        "y": 4
      },
      "id": 1,
      "options": {
        "legend": {
          "calcs": [],
          "displayMode": "hidden",
          "placement": "right",
          "showLegend": false
        },
        "tooltip": {
          "maxHeight": 600,
          "mode": "single",
          "sort": "none"
        }
      },
      "targets": [
        {
          "alias": "",
          "bucketAggs": [
            {
              "field": "timestamp",
              "id": "2",
              "settings": {
                "interval": "auto"
              },
              "type": "date_histogram"
            }
          ],
          "datasource": {
            "type": "grafana-opensearch-datasource",
            "uid": "bdnts6dprmnlsc"
          },
          "format": "table",
          "metrics": [
            {
              "field": "metrics.humidity.lng",
              "id": "3",
              "type": "avg"
            },
            {
              "field": "metrics.humidity.dbl",
              "id": "4",
              "type": "avg"
            }
          ],
          "query": "metrics.sensor_type.str:$sensor_type AND metrics.sensor_id.str:$sensor_id",
          "queryType": "lucene",
          "refId": "A",
          "timeField": "timestamp"
        }
      ],
      "title": "Humidade Relativa do Ar",
      "type": "timeseries"
    },
    {
      "datasource": {
        "type": "grafana-opensearch-datasource",
        "uid": "bdnts6dprmnlsc"
      },
      "fieldConfig": {
        "defaults": {
          "color": {
            "mode": "continuous-GrYlRd",
            "seriesBy": "max"
          },
          "custom": {
            "axisBorderShow": false,
            "axisCenteredZero": false,
            "axisColorMode": "text",
            "axisLabel": "",
            "axisPlacement": "auto",
            "barAlignment": 0,
            "drawStyle": "bars",
            "fillOpacity": 0,
            "gradientMode": "scheme",
            "hideFrom": {
              "legend": false,
              "tooltip": false,
              "viz": false
            },
            "insertNulls": false,
            "lineInterpolation": "linear",
            "lineWidth": 1,
            "pointSize": 5,
            "scaleDistribution": {
              "type": "linear"
            },
            "showPoints": "auto",
            "spanNulls": false,
            "stacking": {
              "group": "A",
              "mode": "none"
            },
            "thresholdsStyle": {
              "mode": "off"
            }
          },
          "mappings": [],
          "thresholds": {
            "mode": "absolute",
            "steps": [
              {
                "color": "green"
              },
              {
                "color": "red",
                "value": 80
              }
            ]
          },
          "unit": "celsius"
        },
        "overrides": []
      },
      "gridPos": {
        "h": 8,
        "w": 12,
        "x": 12,
        "y": 4
      },
      "id": 6,
      "options": {
        "legend": {
          "calcs": [],
          "displayMode": "list",
          "placement": "bottom",
          "showLegend": true
        },
        "tooltip": {
          "maxHeight": 600,
          "mode": "single",
          "sort": "none"
        }
      },
      "pluginVersion": "11.0.0",
      "targets": [
        {
          "alias": "",
          "bucketAggs": [
            {
              "field": "timestamp",
              "id": "4",
              "settings": {
                "interval": "auto",
                "min_doc_count": "0",
                "trimEdges": "0"
              },
              "type": "date_histogram"
            }
          ],
          "datasource": {
            "type": "grafana-opensearch-datasource",
            "uid": "bdnts6dprmnlsc"
          },
          "format": "table",
          "metrics": [
            {
              "field": "metrics.temperature.dbl",
              "id": "1",
              "type": "avg"
            },
            {
              "field": "metrics.temperature.lng",
              "id": "3",
              "type": "avg"
            }
          ],
          "query": "metrics.sensor_type.str:$sensor_type AND metrics.sensor_id.str:$sensor_id",
          "queryType": "lucene",
          "refId": "A",
          "timeField": "timestamp"
        }
      ],
      "title": "Temperatura Cº",
      "type": "timeseries"
    },
    {
      "datasource": {
        "type": "grafana-opensearch-datasource",
        "uid": "bdnts6dprmnlsc"
      },
      "fieldConfig": {
        "defaults": {
          "color": {
            "mode": "continuous-GrYlRd"
          },
          "custom": {
            "axisBorderShow": false,
            "axisCenteredZero": false,
            "axisColorMode": "text",
            "axisLabel": "",
            "axisPlacement": "auto",
            "barAlignment": 0,
            "drawStyle": "line",
            "fillOpacity": 20,
            "gradientMode": "scheme",
            "hideFrom": {
              "legend": false,
              "tooltip": false,
              "viz": false
            },
            "insertNulls": false,
            "lineInterpolation": "smooth",
            "lineWidth": 3,
            "pointSize": 5,
            "scaleDistribution": {
              "type": "linear"
            },
            "showPoints": "auto",
            "spanNulls": false,
            "stacking": {
              "group": "A",
              "mode": "none"
            },
            "thresholdsStyle": {
              "mode": "off"
            }
          },
          "mappings": [],
          "thresholds": {
            "mode": "absolute",
            "steps": [
              {
                "color": "green"
              },
              {
                "color": "red",
                "value": 80
              }
            ]
          },
          "unit": "watt"
        },
        "overrides": []
      },
      "gridPos": {
        "h": 8,
        "w": 12,
        "x": 0,
        "y": 12
      },
      "id": 8,
      "options": {
        "legend": {
          "calcs": [],
          "displayMode": "hidden",
          "placement": "right",
          "showLegend": false
        },
        "tooltip": {
          "maxHeight": 600,
          "mode": "single",
          "sort": "none"
        }
      },
      "targets": [
        {
          "alias": "",
          "bucketAggs": [
            {
              "field": "timestamp",
              "id": "2",
              "settings": {
                "interval": "auto"
              },
              "type": "date_histogram"
            }
          ],
          "datasource": {
            "type": "grafana-opensearch-datasource",
            "uid": "bdnts6dprmnlsc"
          },
          "format": "table",
          "metrics": [
            {
              "field": "metrics.power.dbl",
              "id": "1",
              "type": "avg"
            },
            {
              "field": "metrics.power.lng",
              "id": "3",
              "type": "avg"
            }
          ],
          "query": "",
          "queryType": "lucene",
          "refId": "A",
          "timeField": "timestamp"
        }
      ],
      "title": "Potência Energética",
      "type": "timeseries"
    },
    {
      "datasource": {
        "type": "grafana-opensearch-datasource",
        "uid": "bdnts6dprmnlsc"
      },
      "fieldConfig": {
        "defaults": {
          "color": {
            "mode": "continuous-GrYlRd"
          },
          "custom": {
            "axisBorderShow": false,
            "axisCenteredZero": false,
            "axisColorMode": "text",
            "axisLabel": "",
            "axisPlacement": "auto",
            "barAlignment": 0,
            "drawStyle": "line",
            "fillOpacity": 20,
            "gradientMode": "scheme",
            "hideFrom": {
              "legend": false,
              "tooltip": false,
              "viz": false
            },
            "insertNulls": false,
            "lineInterpolation": "smooth",
            "lineWidth": 3,
            "pointSize": 5,
            "scaleDistribution": {
              "type": "linear"
            },
            "showPoints": "auto",
            "spanNulls": false,
            "stacking": {
              "group": "A",
              "mode": "none"
            },
            "thresholdsStyle": {
              "mode": "off"
            }
          },
          "mappings": [],
          "thresholds": {
            "mode": "absolute",
            "steps": [
              {
                "color": "green"
              },
              {
                "color": "red",
                "value": 80
              }
            ]
          },
          "unit": "volt"
        },
        "overrides": []
      },
      "gridPos": {
        "h": 8,
        "w": 12,
        "x": 12,
        "y": 12
      },
      "id": 9,
      "options": {
        "legend": {
          "calcs": [],
          "displayMode": "hidden",
          "placement": "right",
          "showLegend": false
        },
        "tooltip": {
          "maxHeight": 600,
          "mode": "single",
          "sort": "none"
        }
      },
      "targets": [
        {
          "alias": "",
          "bucketAggs": [
            {
              "field": "timestamp",
              "id": "2",
              "settings": {
                "interval": "auto"
              },
              "type": "date_histogram"
            }
          ],
          "datasource": {
            "type": "grafana-opensearch-datasource",
            "uid": "bdnts6dprmnlsc"
          },
          "format": "table",
          "metrics": [
            {
              "field": "metrics.current.dbl",
              "id": "1",
              "type": "avg"
            },
            {
              "field": "metrics.current.lng",
              "id": "3",
              "type": "avg"
            }
          ],
          "query": "",
          "queryType": "lucene",
          "refId": "A",
          "timeField": "timestamp"
        }
      ],
      "title": "Corrente",
      "type": "timeseries"
    }
  ],
  "refresh": "",
  "schemaVersion": 39,
  "tags": [],
  "templating": {
    "list": [
      {
        "current": {
          "selected": false,
          "text": "All",
          "value": "$__all"
        },
        "datasource": {
          "type": "mysql",
          "uid": "bdoib2zt0zj7ke"
        },
        "definition": "select sensor_type from sensor;",
        "hide": 0,
        "includeAll": true,
        "label": "Tipo de Sensor",
        "multi": true,
        "name": "sensor_type",
        "options": [],
        "query": "select sensor_type from sensor;",
        "refresh": 1,
        "regex": "",
        "skipUrlSync": false,
        "sort": 0,
        "type": "query"
      },
      {
        "current": {
          "selected": false,
          "text": "2C:3A:E8:0B:AC:18",
          "value": "2C:3A:E8:0B:AC:18"
        },
        "datasource": {
          "type": "mysql",
          "uid": "bdoib2zt0zj7ke"
        },
        "definition": "select sensor_id from sensor",
        "hide": 0,
        "includeAll": true,
        "label": "Sensor",
        "multi": true,
        "name": "sensor_id",
        "options": [],
        "query": "select sensor_id from sensor",
        "refresh": 1,
        "regex": "",
        "skipUrlSync": false,
        "sort": 0,
        "type": "query"
      },
      {
        "allValue": "",
        "current": {
          "selected": false,
          "text": "All",
          "value": "$__all"
        },
        "datasource": {
          "type": "mysql",
          "uid": "bdoib2zt0zj7ke"
        },
        "definition": "select building_name from building",
        "description": "",
        "hide": 0,
        "includeAll": true,
        "label": "Prédio",
        "multi": true,
        "name": "building_name",
        "options": [],
        "query": "select building_name from building",
        "refresh": 1,
        "regex": "",
        "skipUrlSync": false,
        "sort": 0,
        "type": "query"
      },
      {
        "current": {
          "selected": false,
          "text": "ICMC",
          "value": "ICMC"
        },
        "datasource": {
          "type": "mysql",
          "uid": "bdoib2zt0zj7ke"
        },
        "definition": "select site_name from site",
        "hide": 0,
        "includeAll": true,
        "label": "Campus",
        "multi": true,
        "name": "site_name",
        "options": [],
        "query": "select site_name from site",
        "refresh": 1,
        "regex": "",
        "skipUrlSync": false,
        "sort": 1,
        "type": "query"
      },
      {
        "current": {
          "selected": false,
          "text": "LAB1008",
          "value": "LAB1008"
        },
        "datasource": {
          "type": "mysql",
          "uid": "bdoib2zt0zj7ke"
        },
        "definition": "select room_number from room",
        "hide": 0,
        "includeAll": true,
        "label": "Sala",
        "multi": true,
        "name": "room",
        "options": [],
        "query": "select room_number from room",
        "refresh": 1,
        "regex": "",
        "skipUrlSync": false,
        "sort": 0,
        "type": "query"
      },
      {
        "current": {
          "selected": false,
          "text": "laboratory",
          "value": "laboratory"
        },
        "datasource": {
          "type": "mysql",
          "uid": "bdoib2zt0zj7ke"
        },
        "definition": "select room_type from room",
        "hide": 0,
        "includeAll": true,
        "label": "Tipo de Sala",
        "multi": true,
        "name": "room_type",
        "options": [],
        "query": "select room_type from room",
        "refresh": 1,
        "regex": "",
        "skipUrlSync": false,
        "sort": 0,
        "type": "query"
      }
    ]
  },
  "time": {
    "from": "now-6h",
    "to": "now"
  },
  "timeRangeUpdatedDuringEditOrView": false,
  "timepicker": {},
  "timezone": "browser",
  "title": "Monitoramento do Sistema de Arrefecimento Estudantil ( ICMC - USP )",
  "uid": "cdnwk572bwdmof",
  "version": 34,
  "weekStart": ""
}
#include <stdlib.h>
#include <stdio.h>

#include <osrmc.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s monaco.osrm", argv[0]);
    goto usage_failure;
  }

  osrmc_config_t config = osrmc_config_construct(argv[1]);

  if (!config) {
    fprintf(stderr, "Error: unable to construct engine config");
    goto config_failure;
  }

  osrmc_osrm_t osrm = osrmc_osrm_construct(config);

  if (!osrm) {
    fprintf(stderr, "Error: unable to construct routing machine");
    goto osrm_failure;
  }

  osrmc_route_params_t params = osrmc_route_params_construct();

  if (!params) {
    fprintf(stderr, "Error: unable to construct route parameters");
    goto params_failure;
  }

  osrmc_route_params_add_coordinate(params, 7.419758, 43.731142);
  osrmc_route_params_add_coordinate(params, 7.419505, 43.736825);

  osrmc_route_response_t response = osrmc_route(osrm, params);

  if (!response) {
    fprintf(stderr, "Error: unable to construct route response");
    goto response_failure;
  }

  const float distance = osrmc_route_response_distance(response);
  const float duration = osrmc_route_response_duration(response);

  printf("Distance: %.0f meters\n", distance);
  printf("Duration: %.0f second\n", duration);

  return EXIT_SUCCESS;


response_failure:
  osrmc_route_response_destruct(response);
params_failure:
  osrmc_route_params_destruct(params);
osrm_failure:
  osrmc_osrm_destruct(osrm);
config_failure:
  osrmc_config_destruct(config);
usage_failure:
  return EXIT_FAILURE;
}
// Copyright (c) 2019 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

#include "carla/NonCopyable.h"
// #include "carla/AtomicList.h"
// #include "carla/client/detail/EpisodeState.h"
// #include "carla/geom/BoundingBox.h"
#include "carla/geom/Location.h"
#include "carla/nav/WalkerEvent.h"
// #include "carla/geom/Transform.h"
#include "carla/rpc/ActorId.h"
// #include <recast/Recast.h>
// #include <recast/DetourCrowd.h>
// #include <recast/DetourNavMesh.h>
// #include <recast/DetourNavMeshBuilder.h>
// #include <recast/DetourNavMeshQuery.h>
// #include <recast/DetourCommon.h>

namespace carla {
namespace nav {

	class Navigation;

	enum WalkerState {
		WALKER_IDLE,
		WALKER_WALKING,
		WALKER_IN_EVENT,
		WALKER_STOP
	}; 

	struct WalkerRoutePoint {
		WalkerEvent event;
		carla::geom::Location location;
		WalkerRoutePoint(WalkerEvent ev, carla::geom::Location loc) : event(ev), location(loc) {};
	};

	struct WalkerInfo {
		carla::geom::Location from;
		carla::geom::Location to;
		int currentIndex { 0 };
		WalkerState state;
		std::vector<WalkerRoutePoint> route;
	};

  class WalkerManager : private NonCopyable {

  public:

    WalkerManager();
    ~WalkerManager();

	/// assign the navigation module
	void SetNav(Navigation *nav) { _nav = nav; };

	/// create a new walker route
    bool AddWalker(ActorId id, carla::geom::Location from);

	/// remove a walker route
    bool RemoveWalker(ActorId id);

	/// update all routes
    bool Update(double delta);

	/// set a new route from its current position
    bool SetWalkerRoute(ActorId id, carla::geom::Location to);

	/// set the next point in the route
    bool SetWalkerNextPoint(ActorId id);

	private:

    bool ExecuteEvent(WalkerInfo &info, double delta);

    std::unordered_map<ActorId, WalkerInfo> _walkers;
	Navigation *_nav { nullptr };
  };

} // namespace nav
} // namespace carla

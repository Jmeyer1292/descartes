/*
 * Software License Agreement (Apache License)
 *
 * Copyright (c) 2014, Southwest Research Institute
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 * process_path.h
 *
 *  Created on: Jun 5, 2014
 *      Author: Dan Solomon
 */

#ifndef PROCESS_PATH_H_
#define PROCESS_PATH_H_

#include "descartes_path_planning/process_pt.h"

namespace descartes
{

typedef std::vector<ProcessPt> ProcessPtVector;

class ProcessPath
{
public:
  ProcessPath() {};
  virtual ~ProcessPath() {};

protected:
  ProcessPtVector pts_;
};

} /* namespace descartes */
#endif /* PROCESS_PATH_H_ */

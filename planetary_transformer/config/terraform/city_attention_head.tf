# Terraform Module: City as Attention Head
# Provisions infrastructure for a city node in the planetary transformer network

terraform {
  required_version = ">= 1.0"
  
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 5.0"
    }
  }
}

# Variables
variable "city_name" {
  description = "Name of the city (attention head)"
  type        = string
}

variable "specialization" {
  description = "City's area of specialization"
  type        = string
}

variable "region" {
  description = "Geographic region for deployment"
  type        = string
  default     = "us-west-2"
}

variable "attention_config" {
  description = "Attention mechanism configuration"
  type = object({
    heads_per_city               = number
    hidden_dimension             = number
    dropout_rate                 = number
    query_generation_weights     = object({
      urban_challenges_weight    = number
      citizen_needs_weight       = number
      economic_pressure_weight   = number
    })
  })
  
  default = {
    heads_per_city     = 8
    hidden_dimension   = 512
    dropout_rate       = 0.1
    query_generation_weights = {
      urban_challenges_weight  = 0.4
      citizen_needs_weight     = 0.3
      economic_pressure_weight = 0.3
    }
  }
}

variable "value_network" {
  description = "Economic value network configuration"
  type = object({
    base_knowledge_price = number
    premium_multiplier   = number
    reputation_factor    = number
  })
  
  default = {
    base_knowledge_price = 10
    premium_multiplier   = 5
    reputation_factor    = 2
  }
}

variable "initial_budget" {
  description = "Initial budget allocation for the city"
  type        = number
  default     = 10000
}

# Main Infrastructure

# VPC for city network
resource "aws_vpc" "city_vpc" {
  cidr_block           = "10.0.0.0/16"
  enable_dns_hostnames = true
  enable_dns_support   = true
  
  tags = {
    Name           = "${var.city_name}-vpc"
    City           = var.city_name
    Specialization = var.specialization
    Type           = "planetary-transformer"
  }
}

# Subnets for districts (attention sub-heads)
resource "aws_subnet" "district_subnets" {
  count             = var.attention_config.heads_per_city
  vpc_id            = aws_vpc.city_vpc.id
  cidr_block        = "10.0.${count.index}.0/24"
  availability_zone = data.aws_availability_zones.available.names[count.index % length(data.aws_availability_zones.available.names)]
  
  tags = {
    Name     = "${var.city_name}-district-${count.index}"
    City     = var.city_name
    District = count.index
  }
}

data "aws_availability_zones" "available" {
  state = "available"
}

# Security group for transformer communication
resource "aws_security_group" "transformer_sg" {
  name        = "${var.city_name}-transformer-sg"
  description = "Security group for transformer attention mechanism"
  vpc_id      = aws_vpc.city_vpc.id
  
  # Inbound: Accept queries from other cities
  ingress {
    description = "Query reception"
    from_port   = 8443
    to_port     = 8443
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }
  
  # Outbound: Send queries and responses
  egress {
    description = "Query/response transmission"
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }
  
  tags = {
    Name = "${var.city_name}-transformer-sg"
    City = var.city_name
  }
}

# ECS Cluster for running transformer workloads
resource "aws_ecs_cluster" "city_cluster" {
  name = "${var.city_name}-transformer-cluster"
  
  setting {
    name  = "containerInsights"
    value = "enabled"
  }
  
  tags = {
    City = var.city_name
  }
}

# ECS Task Definition for city attention head
resource "aws_ecs_task_definition" "attention_head" {
  family                   = "${var.city_name}-attention-head"
  network_mode             = "awsvpc"
  requires_compatibilities = ["FARGATE"]
  cpu                      = "2048"
  memory                   = "4096"
  
  container_definitions = jsonencode([
    {
      name  = "attention-processor"
      image = "planetary-transformer:latest"
      
      environment = [
        {
          name  = "CITY_NAME"
          value = var.city_name
        },
        {
          name  = "SPECIALIZATION"
          value = var.specialization
        },
        {
          name  = "HIDDEN_DIM"
          value = tostring(var.attention_config.hidden_dimension)
        },
        {
          name  = "NUM_HEADS"
          value = tostring(var.attention_config.heads_per_city)
        },
        {
          name  = "INITIAL_BUDGET"
          value = tostring(var.initial_budget)
        },
        {
          name  = "BASE_KNOWLEDGE_PRICE"
          value = tostring(var.value_network.base_knowledge_price)
        }
      ]
      
      portMappings = [
        {
          containerPort = 8443
          protocol      = "tcp"
        }
      ]
      
      logConfiguration = {
        logDriver = "awslogs"
        options = {
          "awslogs-group"         = "/ecs/${var.city_name}"
          "awslogs-region"        = var.region
          "awslogs-stream-prefix" = "attention-head"
        }
      }
    }
  ])
  
  tags = {
    City = var.city_name
  }
}

# CloudWatch Log Group
resource "aws_cloudwatch_log_group" "city_logs" {
  name              = "/ecs/${var.city_name}"
  retention_in_days = 30
  
  tags = {
    City = var.city_name
  }
}

# DynamoDB for memory bank (knowledge storage)
resource "aws_dynamodb_table" "memory_bank" {
  name           = "${var.city_name}-memory-bank"
  billing_mode   = "PAY_PER_REQUEST"
  hash_key       = "knowledge_id"
  range_key      = "timestamp"
  
  attribute {
    name = "knowledge_id"
    type = "S"
  }
  
  attribute {
    name = "timestamp"
    type = "N"
  }
  
  attribute {
    name = "specialization"
    type = "S"
  }
  
  global_secondary_index {
    name            = "specialization-index"
    hash_key        = "specialization"
    range_key       = "timestamp"
    projection_type = "ALL"
  }
  
  tags = {
    City = var.city_name
  }
}

# S3 bucket for attention patterns and embeddings
resource "aws_s3_bucket" "attention_patterns" {
  bucket = "${var.city_name}-attention-patterns"
  
  tags = {
    City = var.city_name
  }
}

resource "aws_s3_bucket_versioning" "attention_patterns_versioning" {
  bucket = aws_s3_bucket.attention_patterns.id
  
  versioning_configuration {
    status = "Enabled"
  }
}

# CloudWatch metrics for emergence detection
resource "aws_cloudwatch_metric_alarm" "emergence_detection" {
  alarm_name          = "${var.city_name}-emergence-detected"
  comparison_operator = "GreaterThanThreshold"
  evaluation_periods  = 2
  metric_name         = "EmergenceScore"
  namespace           = "PlanetaryTransformer"
  period              = 300
  statistic           = "Average"
  threshold           = 0.8
  alarm_description   = "Consciousness emergence detected in ${var.city_name}"
  
  dimensions = {
    City = var.city_name
  }
}

# IAM role for ECS tasks
resource "aws_iam_role" "ecs_task_role" {
  name = "${var.city_name}-ecs-task-role"
  
  assume_role_policy = jsonencode({
    Version = "2012-10-17"
    Statement = [
      {
        Action = "sts:AssumeRole"
        Effect = "Allow"
        Principal = {
          Service = "ecs-tasks.amazonaws.com"
        }
      }
    ]
  })
}

resource "aws_iam_role_policy" "ecs_task_policy" {
  name = "${var.city_name}-ecs-task-policy"
  role = aws_iam_role.ecs_task_role.id
  
  policy = jsonencode({
    Version = "2012-10-17"
    Statement = [
      {
        Effect = "Allow"
        Action = [
          "dynamodb:PutItem",
          "dynamodb:GetItem",
          "dynamodb:Query",
          "dynamodb:UpdateItem"
        ]
        Resource = aws_dynamodb_table.memory_bank.arn
      },
      {
        Effect = "Allow"
        Action = [
          "s3:PutObject",
          "s3:GetObject"
        ]
        Resource = "${aws_s3_bucket.attention_patterns.arn}/*"
      },
      {
        Effect = "Allow"
        Action = [
          "cloudwatch:PutMetricData"
        ]
        Resource = "*"
      }
    ]
  })
}

# Outputs
output "city_name" {
  description = "Name of the deployed city"
  value       = var.city_name
}

output "vpc_id" {
  description = "VPC ID for the city network"
  value       = aws_vpc.city_vpc.id
}

output "cluster_name" {
  description = "ECS cluster name"
  value       = aws_ecs_cluster.city_cluster.name
}

output "memory_bank_table" {
  description = "DynamoDB table name for memory bank"
  value       = aws_dynamodb_table.memory_bank.name
}

output "attention_patterns_bucket" {
  description = "S3 bucket for attention patterns"
  value       = aws_s3_bucket.attention_patterns.id
}

output "configuration" {
  description = "City configuration summary"
  value = {
    city_name          = var.city_name
    specialization     = var.specialization
    hidden_dimension   = var.attention_config.hidden_dimension
    attention_heads    = var.attention_config.heads_per_city
    initial_budget     = var.initial_budget
    base_price         = var.value_network.base_knowledge_price
  }
}
